#include "SBPUsageCategoryBase.h"

void SBPUsageCategoryBase::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SAssignNew(HeaderArea, SBox)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SAssignNew(StatsArea, SBox)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SAssignNew(BodyArea, SBox)
		]
	];
}

void SBPUsageCategoryBase::SetCategoryEntry(TSharedPtr<FBPUsageCategoryEntry> InEntry, UBlueprint* InBlueprint)
{
	Entry = InEntry;
	Blueprint = InBlueprint;

	Initialize();
	
	HeaderArea->SetContent(BuildHeaderWidget());
	StatsArea->SetContent(BuildStatsWidget());
	BodyArea->SetContent(BuildBodyWidget());
}
