// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEditorManager_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_EditorManager;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_EditorManager()
	{
		if (!Z_Registration_Info_UPackage__Script_EditorManager.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/EditorManager",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000040,
				0x88821405,
				0x40AFF4E7,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_EditorManager.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_EditorManager.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_EditorManager(Z_Construct_UPackage__Script_EditorManager, TEXT("/Script/EditorManager"), Z_Registration_Info_UPackage__Script_EditorManager, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x88821405, 0x40AFF4E7));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
