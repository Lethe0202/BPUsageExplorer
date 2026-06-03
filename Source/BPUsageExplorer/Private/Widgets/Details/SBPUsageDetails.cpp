#include "SBPUsageDetails.h"

#include "BPUsageExplorerItemPCH.h"
#include "Category/SBPUsageCategoryVariables.h"
#include "Entry/BPUsageEntry.h"
#include "Item/SBPUsageItemBase.h"

void SBPUsageDetails::Construct(const FArguments& InArgs)
{
    Blueprint = InArgs._Blueprint;
    
    RegisterCategoryFactory();
    
    ChildSlot
    [
        SAssignNew(ContentBox, SBox)
        .HAlign(HAlign_Center)
        .VAlign(VAlign_Center)
    ];
}

void SBPUsageDetails::RegisterCategoryFactory()
{
    CategoryWidgetFactoryMap.Add(BPUsageCategoryNames::Variables, &SBPUsageCategoryVariables::Create);
}

TSharedPtr<SBPUsageCategoryBase> SBPUsageDetails::CreateCategoryWidget(TSharedPtr<FBPUsageCategoryEntry> Entry, const FName& Category)
{
    if (!Blueprint.IsValid()) return nullptr;
    if (!Entry.IsValid()) return nullptr;
    
    FCategoryCreator* CategoryCreator = CategoryWidgetFactoryMap.Find(Category);
    if (CategoryCreator == nullptr) return nullptr;
    
    // 함수 포인터 LUT로 카테고리 위젯 생성 및 초기화
    if (TSharedPtr<SBPUsageCategoryBase> BPUsageCategoryBase = (*CategoryCreator)())
    {
        BPUsageCategoryBase->SetCategoryEntry(Entry, Blueprint.Get());
        
        return BPUsageCategoryBase;
    }
    
    return nullptr;
}

void SBPUsageDetails::SetSelectedEntry(TSharedPtr<FBPUsageEntry> Entry)
{
    if (!Entry.IsValid()) return;

    ContentBox->SetContent(SNullWidget::NullWidget);
    
    if (Entry->GetEntryType() == EBPUsageEntryType::Category)
    {
        TSharedPtr<FBPUsageCategoryEntry> CategoryEntry = StaticCastSharedPtr<FBPUsageCategoryEntry>(Entry);

        // 카테고리 위젯 생성
        if(CategoryEntry->GetCategory() == BPUsageCategoryNames::Variables)
        {
            if (TSharedPtr<SBPUsageCategoryBase> BPUsageCategory = CreateCategoryWidget(CategoryEntry, BPUsageCategoryNames::Variables))
            {
                ContentBox->SetContent(BPUsageCategory.ToSharedRef());
            }
        }
    }
}
