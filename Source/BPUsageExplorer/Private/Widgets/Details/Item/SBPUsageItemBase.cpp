#include "SBPUsageItemBase.h"

void SBPUsageItemBase::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(STextBlock)
		.Text(FText::FromString(TEXT("SBPUsageItemBase")))
	];
}
