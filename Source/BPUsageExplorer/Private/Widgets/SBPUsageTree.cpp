#include "SBPUsageTree.h"
#include "BPUsageExplorerItemPCH.h"
#include "Widgets/Input/SSearchBox.h"

#define LOCTEXT_NAMESPACE "SBPUsageTree"

void SBPUsageTree::Construct(const FArguments& InArgs)
{
	Blueprint = MakeWeakObjectPtr(InArgs._Blueprint);

	OnEntrySelected = InArgs._OnEntrySelected;
	
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(5)
		[
			SAssignNew(SearchBox, SSearchBox)
			.OnTextChanged(this, &SBPUsageTree::HandleSearchBoxTextChanged)
			.OnTextCommitted(this, &SBPUsageTree::HandleSearchBoxTextCommited)
		]
        + SVerticalBox::Slot()
        .FillHeight(1.f)
        [
            SAssignNew(BPUsageTreeView, STreeView<TSharedPtr<FBPUsageEntry>>)
            .TreeItemsSource(&RootItems)
            .OnGenerateRow(this, &SBPUsageTree::HandleTreeViewGenerateRow)
            .OnGetChildren(this, &SBPUsageTree::HandleTreeViewGetChildren)
            .OnSelectionChanged(this, &SBPUsageTree::HandleTreeViewSelectionChanged)
            .SelectionMode(ESelectionMode::Single)
        ]
	];

	RefreshTree();
}

void SBPUsageTree::HandleSearchBoxTextChanged(const FText& InText)
{
}

void SBPUsageTree::HandleSearchBoxTextCommited(const FText& InText, ETextCommit::Type CommitType)
{
}

TSharedRef<class ITableRow> SBPUsageTree::HandleTreeViewGenerateRow(TSharedPtr<FBPUsageEntry> Entry, const TSharedRef<STableViewBase>& OwnerTable)
{
	// 카테고리 헤더 — Bold 텍스트
	if (Entry->GetEntryType() == EBPUsageEntryType::Category)
	{
		return SNew(STableRow<TSharedPtr<FBPUsageEntry>>, OwnerTable)
		[
			SNew(STextBlock)
			.Text(Entry->GetDisplayName())
			.Font(FCoreStyle::GetDefaultFontStyle("Bold", 10))
		];
	}
	
	// 실제 아이템
	TSharedPtr<FBPUsageItemEntry> ItemEntry = StaticCastSharedPtr<FBPUsageItemEntry>(Entry);
	return SNew(STableRow<TSharedPtr<FBPUsageEntry>>, OwnerTable)
	[
		SNew(SHorizontalBox)
		
		// 이름
		+ SHorizontalBox::Slot()
		.FillWidth(1.f)
		[
			SNew(STextBlock)
			.Text(ItemEntry->GetDisplayName())
		]
	];
}

void SBPUsageTree::HandleTreeViewGetChildren(TSharedPtr<FBPUsageEntry> Entry, TArray<TSharedPtr<FBPUsageEntry>>& OutChildren)
{
	OutChildren = Entry->GetChildren();
}

void SBPUsageTree::HandleTreeViewSelectionChanged(TSharedPtr<FBPUsageEntry> Entry, ESelectInfo::Type SelectInfo)
{
	if (Entry.IsValid())
	{
		OnEntrySelected.ExecuteIfBound(Entry);
	}
}

void SBPUsageTree::RefreshTree()
{
    RootItems.Reset();
	
    if (!Blueprint.IsValid()) return;
	
    // 카테고리 생성
    TSharedPtr<FBPUsageCategoryEntry> VariablesCategory = MakeShared<FBPUsageCategoryEntry>(BPUsageCategoryNames::Variables);
    TSharedPtr<FBPUsageCategoryEntry> FunctionsCategory = MakeShared<FBPUsageCategoryEntry>(BPUsageCategoryNames::Functions);
    TSharedPtr<FBPUsageCategoryEntry> EventsCategory = MakeShared<FBPUsageCategoryEntry>(BPUsageCategoryNames::Events);
    TSharedPtr<FBPUsageCategoryEntry> DispatchersCategory = MakeShared<FBPUsageCategoryEntry>(BPUsageCategoryNames::Dispatchers);
    TSharedPtr<FBPUsageCategoryEntry> MacrosCategory = MakeShared<FBPUsageCategoryEntry>(BPUsageCategoryNames::Macros);
    TSharedPtr<FBPUsageCategoryEntry> ComponentsCategory = MakeShared<FBPUsageCategoryEntry>(BPUsageCategoryNames::Components);
	
    // 변수 수집
    for (FBPVariableDescription& Variable : Blueprint->NewVariables)
    {
        VariablesCategory->AddChild(
            MakeShared<FBPUsageItemEntry>(Variable.VarName, BPUsageCategoryNames::Variables));
    }
	
    // 함수 수집
    for (UEdGraph* FunctionGraph : Blueprint->FunctionGraphs)
    {
        FunctionsCategory->AddChild(
            MakeShared<FBPUsageItemEntry>(FunctionGraph->GetFName(), BPUsageCategoryNames::Functions));
    }
	
    // 이벤트 수집
    for (UEdGraph* EventGraph : Blueprint->UbergraphPages)
    {
    	if (!EventGraph)
    		continue;
    	
        for (UEdGraphNode* Node : EventGraph->Nodes)
        {
        	if (!Node)
        		continue;
        	
            if (UK2Node_Event* EventNode = Cast<UK2Node_Event>(Node))
            {
                EventsCategory->AddChild(
                    MakeShared<FBPUsageItemEntry>(EventNode->GetFunctionName(), BPUsageCategoryNames::Events));
            }
            else if (UK2Node_CustomEvent* CustomEventNode = Cast<UK2Node_CustomEvent>(Node))
            {
                EventsCategory->AddChild(
                    MakeShared<FBPUsageItemEntry>(CustomEventNode->CustomFunctionName, BPUsageCategoryNames::Events));
            }
        }
    }
	
    // 디스패처 수집
    for (FBPVariableDescription& Dispatcher : Blueprint->NewVariables)
    {
        if (Dispatcher.VarType.PinCategory == UEdGraphSchema_K2::PC_MCDelegate)
        {
            DispatchersCategory->AddChild(
                MakeShared<FBPUsageItemEntry>(Dispatcher.VarName, BPUsageCategoryNames::Dispatchers));
        }
    }

    // 매크로 수집
    for (UEdGraph* MacroGraph : Blueprint->MacroGraphs)
    {
        MacrosCategory->AddChild(
            MakeShared<FBPUsageItemEntry>(MacroGraph->GetFName(), BPUsageCategoryNames::Macros));
    }

    // 컴포넌트 수집
    if (USimpleConstructionScript* SCS = Blueprint->SimpleConstructionScript)
    {
        for (USCS_Node* SCSNode : SCS->GetAllNodes())
        {
            ComponentsCategory->AddChild(
                MakeShared<FBPUsageItemEntry>(SCSNode->GetVariableName(), BPUsageCategoryNames::Components));
        }
    }

    // 자식 있는 카테고리만 루트에 추가
    auto AddIfNotEmpty = [&](TSharedPtr<FBPUsageCategoryEntry> Category)
    {
        if (Category->GetChildren().Num() > 0)
        {
            RootItems.Add(Category);
        }
    };
	
    AddIfNotEmpty(VariablesCategory);
    AddIfNotEmpty(FunctionsCategory);
    AddIfNotEmpty(EventsCategory);
    AddIfNotEmpty(DispatchersCategory);
    AddIfNotEmpty(MacrosCategory);
    AddIfNotEmpty(ComponentsCategory);

    if (BPUsageTreeView.IsValid())
    {
	    BPUsageTreeView->RequestTreeRefresh();
    }
}

#undef LOCTEXT_NAMESPACE
