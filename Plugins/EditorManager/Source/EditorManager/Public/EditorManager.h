// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FEditorManagerModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
#pragma region ContentBrowserMenuExtention
	void InitializeContentBrowserMenuExtention();

	TArray<FString> FolderPathsSelected;

	TSharedRef<FExtender> CustomContentBrowserMenuExtender(const TArray<FString>& SelectedPaths);

	void AddContentBrowserMenuEntry(class FMenuBuilder& MenuBuilder);

	void OnDeleteUnusedAssetButtonClicked();
#pragma endregion
};
