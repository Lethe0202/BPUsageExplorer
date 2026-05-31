#pragma once

enum class EBPUsageEntryType : uint8
{
	Category,
	Item
};

/** TreeView Entry Base Class */
class FBPUsageEntry
{
public:
	explicit FBPUsageEntry(FName InCategory)
        : Category(InCategory)
    {}
	virtual ~FBPUsageEntry() = default;

	void AddChild(const TSharedPtr<FBPUsageEntry>& InChild) { Children.Add(InChild); }
	const TArray<TSharedPtr<FBPUsageEntry>>& GetChildren() const { return Children; }
	
	virtual FText GetDisplayName() const = 0;
	virtual FName GetCategory() const = 0;
	virtual EBPUsageEntryType GetEntryType() const = 0;
	
protected:
	TArray<TSharedPtr<FBPUsageEntry>> Children;
   	FName Category;
};

/** TreeView Category */
class FBPUsageCategoryEntry : public FBPUsageEntry
{
public:
   explicit FBPUsageCategoryEntry(FName InCategory)
        : FBPUsageEntry(InCategory)
    {}

	virtual FText GetDisplayName() const override { return FText::FromName(Category); }
	virtual FName GetCategory() const override { return Category; }
	virtual EBPUsageEntryType GetEntryType() const override { return EBPUsageEntryType::Category; }


};

/** TreeView Item */
class FBPUsageItemEntry : public FBPUsageEntry
{
public:
	explicit FBPUsageItemEntry(FName InName, FName InCategory)
		 : FBPUsageEntry(InCategory)
		 , Name(InName)
	{}

	virtual FText GetDisplayName() const override { return FText::FromName(Name); }
	virtual FName GetCategory() const override { return Category; }
	virtual EBPUsageEntryType GetEntryType() const override { return EBPUsageEntryType::Item; }
	bool HasExternal() const { return bHasExternal; }
	void SetHasExternal(bool bInHasExternal) { bHasExternal = bInHasExternal; }

private:
	FName Name;
	bool bHasExternal = false;
};


class SBPUsageTree : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBPUsageTree)
		
	{}
	SLATE_ARGUMENT(TObjectPtr<UBlueprint>, Blueprint)
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
};
