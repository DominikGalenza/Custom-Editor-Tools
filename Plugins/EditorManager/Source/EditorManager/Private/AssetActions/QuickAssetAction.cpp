// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActions/QuickAssetAction.h"
#include "DebugHeader.h"

void UQuickAssetAction::TestFunction()
{
	Print(TEXT("Working"), FColor::Green);
	PrintLog(TEXT("Working"));
}
