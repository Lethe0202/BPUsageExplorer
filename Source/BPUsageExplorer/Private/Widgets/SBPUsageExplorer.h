#pragma once



class SBPUsageExplorer : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBPUsageExplorer)
		
	{}
	SLATE_ARGUMENT(TObjectPtr<UBlueprint>, Blueprint)
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs);
};
