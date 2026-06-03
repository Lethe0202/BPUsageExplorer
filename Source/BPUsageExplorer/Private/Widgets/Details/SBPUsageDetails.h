#pragma once
#include "Category/SBPUsageCategoryBase.h"
#include "Item/SBPUsageItemBase.h"

class FBPUsageEntry;
class SBPUsageCategoryBase;
class SBPUsageItemBase;

class SBPUsageDetails : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBPUsageDetails)
		: _Blueprint(nullptr)
		
	{}
	SLATE_ARGUMENT(TObjectPtr<UBlueprint>, Blueprint)
		
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs);

	/** 선택된 항목으로 Set */
	void SetSelectedEntry(TSharedPtr<FBPUsageEntry> Entry);

private:
	/** 카테고리 Factory 함수 등록 */
	void RegisterCategoryFactory();
	
	/** 선택된 카테고리 Widget 생성 */ 
	TSharedPtr<SBPUsageCategoryBase> CreateCategoryWidget(TSharedPtr<FBPUsageCategoryEntry> Entry, const FName& Category);

protected:
	TWeakObjectPtr<UBlueprint> Blueprint;

private:
	TSharedPtr<SBox> ContentBox;
	
	/** 카테고리 선택 시 */
    TMap<FName, TSharedPtr<SBPUsageCategoryBase>> CategoryWidgetMap;
    
    /** 아이템 선택 시 */
    TMap<FName, TSharedPtr<SBPUsageItemBase>> ItemWidgetMap;
	
	/** 팩토리 함수 포인터 Map */
	using FCategoryCreator = TSharedPtr<SBPUsageCategoryBase>(*)();
	TMap<FName, FCategoryCreator> CategoryWidgetFactoryMap;
	// TMap<FName, SBPUsageItemBase::FCategoryWidgetFactoryy> ItemWidgetFactoryMap;
};
