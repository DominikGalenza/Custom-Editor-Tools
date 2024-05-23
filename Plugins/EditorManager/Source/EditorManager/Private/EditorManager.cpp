// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorManager.h"
#include "ContentBrowserModule.h"
#include "DebugHeader.h"
#include "EditorAssetLibrary.h"
#include "ObjectTools.h"

#define LOCTEXT_NAMESPACE "FEditorManagerModule"

void FEditorManagerModule::StartupModule()
{
	InitializeContentBrowserMenuExtention();
}

void FEditorManagerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#pragma region ContentBrowserMenuExtention
void FEditorManagerModule::InitializeContentBrowserMenuExtention()
{
	FContentBrowserModule& ContentBrowserModule =
	FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));

	TArray<FContentBrowserMenuExtender_SelectedPaths>& ContentBrowserModuleMenuExtenders =
	ContentBrowserModule.GetAllPathViewContextMenuExtenders();

	//FContentBrowserMenuExtender_SelectedPaths CustomContentBrowserMenuDelegate;
	//CustomContentBrowserMenuDelegate.BindRaw(this, &FEditorManagerModule::CustomContentBrowserMenuExtender);

	//ContentBrowserModuleMenuExtenders.Add(CustomContentBrowserMenuDelegate);
	ContentBrowserModuleMenuExtenders.Add(FContentBrowserMenuExtender_SelectedPaths::
	CreateRaw(this, &FEditorManagerModule::CustomContentBrowserMenuExtender));

}

TSharedRef<FExtender> FEditorManagerModule::CustomContentBrowserMenuExtender(const TArray<FString>& SelectedPaths)
{
	TSharedRef<FExtender> MenuExtender(new FExtender());

	if (SelectedPaths.Num() > 0)
	{
		MenuExtender->AddMenuExtension(FName("Delete"),
			EExtensionHook::After,
			TSharedPtr<FUICommandList>(),
			FMenuExtensionDelegate::CreateRaw(this, &FEditorManagerModule::AddContentBrowserMenuEntry));

		FolderPathsSelected = SelectedPaths;
	}
	return MenuExtender;
}

void FEditorManagerModule::AddContentBrowserMenuEntry(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(FText::FromString(TEXT("Delete Unused Assets")),
		FText::FromString(TEXT("Safely delete all unused assets under folder")),
		FSlateIcon(),
		FExecuteAction::CreateRaw(this, &FEditorManagerModule::OnDeleteUnusedAssetButtonClicked));
}

void FEditorManagerModule::OnDeleteUnusedAssetButtonClicked()
{
	if (FolderPathsSelected.Num() > 1)
	{
		DebugHeader::ShowMessageDialog(EAppMsgType::Ok, TEXT("You can only do this to one folder"));
		return;
	}

	TArray<FString> AssetsPathNames = UEditorAssetLibrary::ListAssets(FolderPathsSelected[0]);

	if (AssetsPathNames.Num() == 0)
	{
		DebugHeader::ShowMessageDialog(EAppMsgType::Ok, TEXT("No asset found under selected folder"));
		return;
	}

	EAppReturnType::Type ConfirmResult =
	DebugHeader::ShowMessageDialog(EAppMsgType::YesNo, TEXT("A total of ") + FString::FromInt(AssetsPathNames.Num()) + TEXT(" found.\nWould you like to proceed?"));

	if (ConfirmResult == EAppReturnType::No)
	{
		return;
	}

	TArray<FAssetData> UnusedAssetsDataArray;

	for (const FString& AssetPathName : AssetsPathNames)
	{
		if (AssetPathName.Contains(TEXT("Developers")) || AssetPathName.Contains(TEXT("Collections")))
		{
			continue;
		}

		if (!UEditorAssetLibrary::DoesAssetExist(AssetPathName))
		{
			continue;
		}

		TArray<FString> AssetReferencers = UEditorAssetLibrary::FindPackageReferencersForAsset(AssetPathName);

		if (AssetReferencers.Num() == 0)
		{
			const FAssetData UnusedAssetData = UEditorAssetLibrary::FindAssetData(AssetPathName);
			UnusedAssetsDataArray.Add(UnusedAssetData);
		}
	}

	if (UnusedAssetsDataArray.Num() > 0)
	{
		ObjectTools::DeleteAssets(UnusedAssetsDataArray);
	}
	else
	{
		DebugHeader::ShowMessageDialog(EAppMsgType::Ok, TEXT("No unused asset found under selected folder"));
	}
}
#pragma endregion

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEditorManagerModule, EditorManager)