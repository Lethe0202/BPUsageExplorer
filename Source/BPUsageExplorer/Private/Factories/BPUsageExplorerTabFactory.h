#pragma once
#include "BlueprintEditor.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

class FBPUsageExplorerTabFactory : public FWorkflowTabFactory
{
public:
	FBPUsageExplorerTabFactory(FName InTabName, TSharedPtr<FBlueprintEditor> InEditor);

	 virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
     virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;
    
protected:
	TWeakPtr<FBlueprintEditor> BlueprintEditor;
};
