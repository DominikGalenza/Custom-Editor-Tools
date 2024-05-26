// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorManager.h"
#include "ContentBrowserModule.h"
#include "DebugHeader.h"
#include "EditorAssetLibrary.h"
#include "ObjectTools.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetViewUtils.h"
#include "AssetToolsModule.h"
#include "SlateWidgets/AdvanceDeletionWidget.h"

#define LOCTEXT_NAMESPACE "FEditorManagerModule"

void FEditorManagerModule::StartupModule()
{
	InitializeContentBrowserMenuExtention();

	RegisterAdvanceDeletionTab();
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

	MenuBuilder.AddMenuEntry(FText::FromString(TEXT("Delete Empty Folders")),
		FText::FromString(TEXT("Safely delete all empty folders")),
		FSlateIcon(),
		FExecuteAction::CreateRaw(this, &FEditorManagerModule::OnDeleteEmptyFoldersButtonClicked));

	MenuBuilder.AddMenuEntry(FText::FromString(TEXT("Advance Deletion")),
		FText::FromString(TEXT("List assets by specific condition in a tab for deleting")),
		FSlateIcon(),
		FExecuteAction::CreateRaw(this, &FEditorManagerModule::OnAdvanceDeletionButtonClicked));
}

void FEditorManagerModule::OnDeleteUnusedAssetButtonClicked()
{
	if (FolderPathsSelected.Num() > 1)
	{
		DebugHeader::ShowMessageDialog(EAppMsgType::Ok, TEXT("You can only do this to one folder"), false);
		return;
	}

	TArray<FString> AssetsPathNames = UEditorAssetLibrary::ListAssets(FolderPathsSelected[0]);

	if (AssetsPathNames.Num() == 0)
	{
		DebugHeader::ShowMessageDialog(EAppMsgType::Ok, TEXT("No asset found under selected folder"));
		return;
	}

	EAppReturnType::Type ConfirmResult =
	DebugHeader::ShowMessageDialog(EAppMsgType::YesNo, TEXT("A total of ") + FString::FromInt(AssetsPathNames.Num()) 
		+ TEXT(" assets needs to be checked.\nWould you like to proceed?"), false);

	if (ConfirmResult == EAppReturnType::No)
	{
		return;
	}

	FixUpRedirectors();

	TArray<FAssetData> UnusedAssetsDataArray;

	for (const FString& AssetPathName : AssetsPathNames)
	{
		if (AssetPathName.Contains(TEXT("Developers")) || AssetPathName.Contains(TEXT("Collections"))
			|| AssetPathName.Contains(TEXT("__ExternalActors__")) || AssetPathName.Contains(TEXT("__ExternalObjects__")))
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
		DebugHeader::ShowMessageDialog(EAppMsgType::Ok, TEXT("No unused asset found under selected folder"), false);
	}
}

void FEditorManagerModule::OnDeleteEmptyFoldersButtonClicked()
{
	FixUpRedirectors();

	TArray<FString> FolderPathsArray = UEditorAssetLibrary::ListAssets(FolderPathsSelected[0], true, true);
	uint32 Counter = 0;

	FString EmptyFolderPathsNames;
	TArray<FString> EmptyFoldersPathsArray;

	for (const FString& FolderPath : FolderPathsArray)
	{
		if (FolderPath.Contains(TEXT("Developers")) || FolderPath.Contains(TEXT("Collections"))
			|| FolderPath.Contains(TEXT("__ExternalActors__")) || FolderPath.Contains(TEXT("__ExternalObjects__")))
		{
			continue;
		}

		if (!UEditorAssetLibrary::DoesDirectoryExist(FolderPath))
		{
			continue;
		}

		if (!UEditorAssetLibrary::DoesDirectoryHaveAssets(FolderPath))
		{
			EmptyFolderPathsNames.Append(FolderPath);
			EmptyFolderPathsNames.Append(TEXT("\n"));

			EmptyFoldersPathsArray.Add(FolderPath);
		}
	}

	if (EmptyFoldersPathsArray.Num() == 0)
	{
		DebugHeader::ShowMessageDialog(EAppMsgType::Ok, TEXT("No empty folder found under selected folder"), false);
		return;
	}

	EAppReturnType::Type ConfirmResult = DebugHeader::ShowMessageDialog(EAppMsgType::OkCancel,
		TEXT("Empty folders found in:\n") + EmptyFolderPathsNames + TEXT("\nWould you like to delete all?"), false);

	if (ConfirmResult == EAppReturnType::Cancel)
	{
		return;
	}

	for (const FString& EmptyFolderPath : EmptyFoldersPathsArray)
	{
		if (UEditorAssetLibrary::DeleteDirectory(EmptyFolderPath))
		{
			++Counter;
		}
		else
		{
			DebugHeader::Print(TEXT("Failed to delete " + EmptyFolderPath), FColor::Red);
		}
	}

	if (Counter > 0)
	{
		DebugHeader::ShowNotifyInfo(TEXT("Successfully deleted ") + FString::FromInt(Counter) + TEXT(" folders"));
	}
}

void FEditorManagerModule::OnAdvanceDeletionButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(FName("AdvanceDeletion"));
}

void FEditorManagerModule::FixUpRedirectors()
{
	IAssetRegistry& AssetRegistry =
	FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();

	FARFilter Filter;
	Filter.bRecursivePaths = true;
	Filter.PackagePaths.Emplace("/Game");
	Filter.ClassPaths.Add(UObjectRedirector::StaticClass()->GetClassPathName());

	TArray<FAssetData> AssetList;
	AssetRegistry.GetAssets(Filter, AssetList);


	if (AssetList.Num() == 0)
	{
		return;
	}

	TArray<FString> ObjectPaths;
	for (const FAssetData& Asset : AssetList)
	{
		ObjectPaths.Add(Asset.GetObjectPathString());
	}

	TArray<UObject*> Objects;
	const bool bAllowedToPromptToLoadAssets = true;
	const bool bLoadRedirects = true;

	if (AssetViewUtils::LoadAssetsIfNeeded(ObjectPaths, Objects, bAllowedToPromptToLoadAssets, bLoadRedirects))
	{
		TArray<UObjectRedirector*> Redirectors;
		for (UObject* Object : Objects)
		{
			Redirectors.Add(CastChecked<UObjectRedirector>(Object));
		}

		FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));
		AssetToolsModule.Get().FixupReferencers(Redirectors);
	}
}
#pragma endregion

#pragma region CustomEditorTab
void FEditorManagerModule::RegisterAdvanceDeletionTab()
{
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FName("AdvanceDeletion"),
		FOnSpawnTab::CreateRaw(this, &FEditorManagerModule::OnSpawnAdvanceDeletionTab))
		.SetDisplayName(FText::FromString(TEXT("Advance Deletion")));
}
TSharedRef<SDockTab> FEditorManagerModule::OnSpawnAdvanceDeletionTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab).TabRole(ETabRole::NomadTab)
	[
		SNew(SAdvanceDeletionTab)
			.TestString(TEXT("I am passing data"))
	];
}
#pragma endregion

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEditorManagerModule, EditorManager)