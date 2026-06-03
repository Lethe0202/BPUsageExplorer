#pragma once
#include "Details/Entry/BPUsageEntry.h"


DECLARE_DELEGATE_OneParam(FOnBPUsageEntrySelected, TSharedPtr<FBPUsageEntry>)


class SBPUsageTree : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBPUsageTree)
		
	{}
	SLATE_ARGUMENT(TObjectPtr<UBlueprint>, Blueprint)
	SLATE_EVENT(FOnBPUsageEntrySelected, OnEntrySelected)
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs);
	
protected:
	// --------------------
	// SearchBox
	// --------------------
	void HandleSearchBoxTextChanged(const FText& InText);
	void HandleSearchBoxTextCommited(const FText& InText, ETextCommit::Type CommitType);

	// --------------------
	// TreeView
	// --------------------
	TSharedRef<class ITableRow> HandleTreeViewGenerateRow(TSharedPtr<FBPUsageEntry> Entry, const TSharedRef<STableViewBase>& OwnerTable);
	void HandleTreeViewGetChildren(TSharedPtr<FBPUsageEntry> Entry, TArray<TSharedPtr<FBPUsageEntry>>& OutChildren);
	void HandleTreeViewSelectionChanged(TSharedPtr<FBPUsageEntry> Entry, ESelectInfo::Type SelectInfo);

private:
	void RefreshTree();
	
protected:
	// --------------------
	// SearchBox
	// --------------------
	TSharedPtr<SSearchBox> SearchBox;
	FString SearchFilter;
	
	// --------------------
	// TreeView
	// --------------------
	TSharedPtr<STreeView<TSharedPtr<FBPUsageEntry>>> BPUsageTreeView;
	TArray<TSharedPtr<FBPUsageEntry>> RootItems;

protected:
	TWeakObjectPtr<UBlueprint> Blueprint;

private:
	FOnBPUsageEntrySelected OnEntrySelected;
};
