// Copyright Epic Games, Inc. All Rights Reserved.

#include "XhVr.h"
#include "Type/XhType.h"
#include "Settings/XhVrSettings.h"
#include "Misc/CoreDelegates.h"
#include "Misc/App.h"
#if WITH_EDITOR
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "PropertyEditorModule.h"
#endif

#define LOCTEXT_NAMESPACE "FXhVrModule"

void FXhVrModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UXhVrSettings* Settings = GetMutableDefault<UXhVrSettings>();
	if (Settings)
	{
		Settings->bEnableLog = true;
		Settings->LogPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() + TEXT("Xh/"));//FPaths::ProjectContentDir()
		Settings->LogFileName = FApp::GetProjectName();
		Settings->MaxLogSize = 1000000000;

#if WITH_EDITOR
		// register settings
		ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
		if (SettingsModule != nullptr)
		{
			ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "XhVr",
				LOCTEXT("XhVrSettingsName", "XhVr"),
				LOCTEXT("XhVrSettingsDescription", "Configure the XhVr plug-in."),
				Settings
			);
		}
#endif // WITH_EDITOR
	}
}

void FXhVrModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FXhVrModule, XhVr)