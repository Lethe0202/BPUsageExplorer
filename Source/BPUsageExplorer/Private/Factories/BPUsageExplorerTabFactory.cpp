
#include "BPUsageExplorerTabFactory.h"
#include "BPUsageExplorer.h"
#include "Widgets/SBPUsageExplorer.h"

FBPUsageExplorerTabFactory::FBPUsageExplorerTabFactory(FName InTabName, TSharedPtr<FBlueprintEditor> InEditor)
	: FWorkflowTabFactory(InTabName, InEditor)
		,BlueprintEditor(InEditor)
{
	TabLabel = FBPUsageExplorerModule::MyTabTitleText;
	TabIcon  = FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Star");
	bIsSingleton = true;
	ViewMenuDescription = FText::FromString("Custom ViewMenuDescription");
	ViewMenuTooltip = FText::FromString("Custom ViewMenuTooltip");
}

TSharedRef<SWidget> FBPUsageExplorerTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	TObjectPtr<UBlueprint> Blueprint = nullptr;
	if (BlueprintEditor.IsValid())
	{
		Blueprint = Cast<UBlueprint>(BlueprintEditor.Pin()->GetBlueprintObj());
	}
	
    return SNew(SVerticalBox)
    	+ SVerticalBox::Slot()
    	.AutoHeight()
    	[
    		SNew(SBPUsageExplorer)
    		.Blueprint(Blueprint)
    	];
}

FText FBPUsageExplorerTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FWorkflowTabFactory::GetTabToolTipText(Info);
}
