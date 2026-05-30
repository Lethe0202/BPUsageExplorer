
#include "BPUsageExplorerTabFactory.h"
#include "BPUsageExplorer.h"

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
    return SNew(SVerticalBox)
        + SVerticalBox::Slot()
        .AutoHeight()
        .Padding(10.f)
        [
            SNew(STextBlock)
            .Text(FText::FromString("Test Text"))
        ];
}

FText FBPUsageExplorerTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FWorkflowTabFactory::GetTabToolTipText(Info);
}
