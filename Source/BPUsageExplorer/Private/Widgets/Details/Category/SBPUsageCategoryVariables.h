#pragma once
#include "SBPUsageCategoryBase.h"

class SBPUsageCategoryVariables : public SBPUsageCategoryBase
{
public:
	SLATE_BEGIN_ARGS(SBPUsageCategoryVariables) {}
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs);
	
	static TSharedPtr<SBPUsageCategoryBase> Create()
	{
		return SNew(SBPUsageCategoryVariables);
	}

protected:
	virtual void Initialize() override;
	virtual TSharedRef<SWidget> BuildHeaderWidget() override;
	virtual TSharedRef<SWidget> BuildStatsWidget() override;
	virtual TSharedRef<SWidget> BuildBodyWidget() override;
	
private:
	// 분석 결과 데이터
	// TArray<FBPVariableUsageData> VariableData;
};
