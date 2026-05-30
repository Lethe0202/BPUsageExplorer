// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FBPUsageExplorerModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

protected:
	void RegisterBlueprintUsageExplorerTab();

private:
	TSharedRef<SDockTab> SpawnUsageExplorerTab(const FSpawnTabArgs& Args);

public:
	static const FText MyTabTitleText;
};
