// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "EditorManager/Public/AssetActions/QuickAssetAction.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeQuickAssetAction() {}
// Cross Module References
	BLUTILITY_API UClass* Z_Construct_UClass_UAssetActionUtility();
	EDITORMANAGER_API UClass* Z_Construct_UClass_UQuickAssetAction();
	EDITORMANAGER_API UClass* Z_Construct_UClass_UQuickAssetAction_NoRegister();
	UPackage* Z_Construct_UPackage__Script_EditorManager();
// End Cross Module References
	DEFINE_FUNCTION(UQuickAssetAction::execTestFunction)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->TestFunction();
		P_NATIVE_END;
	}
	void UQuickAssetAction::StaticRegisterNativesUQuickAssetAction()
	{
		UClass* Class = UQuickAssetAction::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "TestFunction", &UQuickAssetAction::execTestFunction },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UQuickAssetAction_TestFunction_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UQuickAssetAction_TestFunction_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "ModuleRelativePath", "Public/AssetActions/QuickAssetAction.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickAssetAction_TestFunction_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UQuickAssetAction, nullptr, "TestFunction", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickAssetAction_TestFunction_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickAssetAction_TestFunction_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_UQuickAssetAction_TestFunction()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickAssetAction_TestFunction_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UQuickAssetAction);
	UClass* Z_Construct_UClass_UQuickAssetAction_NoRegister()
	{
		return UQuickAssetAction::StaticClass();
	}
	struct Z_Construct_UClass_UQuickAssetAction_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UQuickAssetAction_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UAssetActionUtility,
		(UObject* (*)())Z_Construct_UPackage__Script_EditorManager,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickAssetAction_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UQuickAssetAction_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UQuickAssetAction_TestFunction, "TestFunction" }, // 1494937662
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickAssetAction_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UQuickAssetAction_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Object" },
		{ "IncludePath", "AssetActions/QuickAssetAction.h" },
		{ "ModuleRelativePath", "Public/AssetActions/QuickAssetAction.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UQuickAssetAction_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UQuickAssetAction>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UQuickAssetAction_Statics::ClassParams = {
		&UQuickAssetAction::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickAssetAction_Statics::Class_MetaDataParams), Z_Construct_UClass_UQuickAssetAction_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_UQuickAssetAction()
	{
		if (!Z_Registration_Info_UClass_UQuickAssetAction.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UQuickAssetAction.OuterSingleton, Z_Construct_UClass_UQuickAssetAction_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UQuickAssetAction.OuterSingleton;
	}
	template<> EDITORMANAGER_API UClass* StaticClass<UQuickAssetAction>()
	{
		return UQuickAssetAction::StaticClass();
	}
	UQuickAssetAction::UQuickAssetAction(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UQuickAssetAction);
	UQuickAssetAction::~UQuickAssetAction() {}
	struct Z_CompiledInDeferFile_FID_UEProjects_ExtendEditor_ExtendEditor_Plugins_EditorManager_Source_EditorManager_Public_AssetActions_QuickAssetAction_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UEProjects_ExtendEditor_ExtendEditor_Plugins_EditorManager_Source_EditorManager_Public_AssetActions_QuickAssetAction_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UQuickAssetAction, UQuickAssetAction::StaticClass, TEXT("UQuickAssetAction"), &Z_Registration_Info_UClass_UQuickAssetAction, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UQuickAssetAction), 3173331484U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UEProjects_ExtendEditor_ExtendEditor_Plugins_EditorManager_Source_EditorManager_Public_AssetActions_QuickAssetAction_h_2080221366(TEXT("/Script/EditorManager"),
		Z_CompiledInDeferFile_FID_UEProjects_ExtendEditor_ExtendEditor_Plugins_EditorManager_Source_EditorManager_Public_AssetActions_QuickAssetAction_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UEProjects_ExtendEditor_ExtendEditor_Plugins_EditorManager_Source_EditorManager_Public_AssetActions_QuickAssetAction_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
