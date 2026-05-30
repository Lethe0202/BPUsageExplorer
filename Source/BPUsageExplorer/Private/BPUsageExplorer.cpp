// Copyright Epic Games, Inc. All Rights Reserved.

#include "BPUsageExplorer.h"

#include "BlueprintEditorModule.h"
#include "Factories/BPUsageExplorerTabFactory.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

#define LOCTEXT_NAMESPACE "FBlueprintUsageExplorerModule"

const FText FBPUsageExplorerModule::MyTabTitleText = LOCTEXT("TabTitle", "BlueprintUsageExplorer");
const FName MyTabName = "UsageExplorer";

void FBPUsageExplorerModule::StartupModule()
{
	RegisterBlueprintUsageExplorerTab();
}

void FBPUsageExplorerModule::ShutdownModule()
{
}

void FBPUsageExplorerModule::RegisterBlueprintUsageExplorerTab()
{
	FBlueprintEditorModule& BlueprintEditorModule = FModuleManager::LoadModuleChecked<FBlueprintEditorModule>("Kismet");

	// 탭 스포너 팩토리 등록
	BlueprintEditorModule.OnRegisterTabsForEditor().AddLambda(
		[this](FWorkflowAllowedTabSet& TabFactories, FName ModeName, TSharedPtr<FBlueprintEditor> Editor)
		{
			// 탭 팩토리 생성 및 등록
			TSharedPtr<FBPUsageExplorerTabFactory> BlueprintUsageExplorerTabFactory = MakeShared<FBPUsageExplorerTabFactory>(MyTabName, Editor);
			TabFactories.RegisterFactory(BlueprintUsageExplorerTabFactory);
		}
	);	
}

TSharedRef<SDockTab> FBPUsageExplorerModule::SpawnUsageExplorerTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::PanelTab)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(STextBlock)
				.Text(FText::FromString("My Custom Window"))
			]
		];
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBPUsageExplorerModule, BlueprintUsageExplorer)