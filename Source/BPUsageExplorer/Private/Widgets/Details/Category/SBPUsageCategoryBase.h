#pragma once
#include "Widgets/Details/Entry/BPUsageEntry.h"

class SBPUsageCategoryBase : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBPUsageCategoryBase)

	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
    void SetCategoryEntry(TSharedPtr<FBPUsageCategoryEntry> InEntry, UBlueprint* InBlueprint);

protected:
	virtual void Initialize() = 0;
	virtual TSharedRef<SWidget> BuildHeaderWidget() = 0;
	virtual TSharedRef<SWidget> BuildStatsWidget() = 0;
	virtual TSharedRef<SWidget> BuildBodyWidget() = 0;
	
protected:
	TSharedPtr<FBPUsageCategoryEntry> Entry;
	TWeakObjectPtr<UBlueprint> Blueprint;

private:
	TSharedPtr<SBox> HeaderArea;
	TSharedPtr<SBox> StatsArea;
	TSharedPtr<SBox> BodyArea;
};
