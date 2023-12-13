// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ToolTipWidget.generated.h"

/**
 * 
 */
UCLASS()
class PHOENIX_API UToolTipWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UToolTipWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Tool Tip Widget")
	TSubclassOf<UUserWidget> ToolTipClassToUse;
	
};
