#include "SBPUsageExplorer.h"

#include "SBPUsageTree.h"
#include "Details/SBPUsageDetails.h"
#include "Widgets/Input/SSearchBox.h"

void SBPUsageExplorer::Construct(const FArguments& InArgs)
{
	ChildSlot
	[	
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.FillWidth(1.f)
		[
			// 카테고리 Tree
			SNew(SBPUsageTree)
			.Blueprint(InArgs._Blueprint)
			.OnEntrySelected(this, &SBPUsageExplorer::HandleEntrySelected)
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.f)
		[
			SAssignNew(BPUsageDetailsPanel, SBPUsageDetails)
			.Blueprint(InArgs._Blueprint)
		]
	];
}

void SBPUsageExplorer::HandleEntrySelected(TSharedPtr<FBPUsageEntry> Entry)
{
	if (BPUsageDetailsPanel.IsValid())
	{
		BPUsageDetailsPanel->SetSelectedEntry(Entry);
	}
}
