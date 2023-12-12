// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h" // IUserObjectListEntry
#include "InteractionListEntry.generated.h"

class UTextBlock;
class UInteractionListEntryObject;

/**
 * 
 */
UCLASS()
class PHOENIX_API UInteractionListEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:

	UInteractionListEntry(const FObjectInitializer& ObjectInitializer);
	
protected:

	UPROPERTY(BlueprintReadOnly, Category = "Interaction List Entry", meta = (BindWidget))
	TObjectPtr<UTextBlock> InteractionText;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(BlueprintReadOnly, Category = "Interaction List Entry")
	UInteractionListEntryObject* InteractionObject;
};
