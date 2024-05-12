// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
#include "QuickAssetAction.generated.h"

/**
 * 
 */
UCLASS()
class EDITORMANAGER_API UQuickAssetAction : public UAssetActionUtility
{
	GENERATED_BODY()

public:
	UFUNCTION(CallInEditor)
	void TestFunction();

	UFUNCTION(CallInEditor)
	void DuplicateAssets(int32 NumberOfDuplicates);
	
};
