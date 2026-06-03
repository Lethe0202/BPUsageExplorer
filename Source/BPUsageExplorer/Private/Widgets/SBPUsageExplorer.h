#pragma once
#include "Details/Entry/BPUsageEntry.h"

class SBPUsageDetails;

class SBPUsageExplorer : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBPUsageExplorer)
		
	{}
	SLATE_ARGUMENT(TObjectPtr<UBlueprint>, Blueprint)
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs);

protected:
	void HandleEntrySelected(TSharedPtr<FBPUsageEntry> Entry);

private:
	TSharedPtr<SBPUsageDetails> BPUsageDetailsPanel;
};
