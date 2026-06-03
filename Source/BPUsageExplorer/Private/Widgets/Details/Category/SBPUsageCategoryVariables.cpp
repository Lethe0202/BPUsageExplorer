#include "SBPUsageCategoryVariables.h"

void SBPUsageCategoryVariables::Construct(const FArguments& InArgs)
{
	SBPUsageCategoryBase::Construct(SBPUsageCategoryBase::FArguments());
}

void SBPUsageCategoryVariables::Initialize()
{
	if (!Blueprint.IsValid()) return;
	
	// TODO: Init Data
}

TSharedRef<SWidget> SBPUsageCategoryVariables::BuildHeaderWidget()
{
	return SNew(STextBlock)
			.Text(FText::FromString(TEXT("HeaderWidget")));
}

TSharedRef<SWidget> SBPUsageCategoryVariables::BuildBodyWidget()
{
	return SNew(STextBlock)
		.Text(FText::FromString(TEXT("BodyWidget")));
}

TSharedRef<SWidget> SBPUsageCategoryVariables::BuildStatsWidget()
{
	return SNew(STextBlock)
			.Text(FText::FromString(TEXT("StatsWidget")));
}


