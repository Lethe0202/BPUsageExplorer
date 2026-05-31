#include "SBPUsageExplorer.h"

#include "SBPUsageDetails.h"
#include "SBPUsageTree.h"
#include "Widgets/Input/SSearchBox.h"

void SBPUsageExplorer::Construct(const FArguments& InArgs)
{
	ChildSlot
	[	
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SBPUsageTree)
			.Blueprint(InArgs._Blueprint)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SBPUsageDetails)
		]
	];
}
