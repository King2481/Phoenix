// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Phoenix/UI/Widgets/ToolTipWidget.h"
#include "Blueprint/IUserObjectListEntry.h" // IUserObjectListEntry
#include "ItemDisplayEntry.generated.h"

class UTextBlock;
class UButton;
class UItemEntryObject;

/**
 * 
 */
UCLASS()
class PHOENIX_API UItemDisplayEntry : public UToolTipWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:

	UItemDisplayEntry(const FObjectInitializer& ObjectInitializer);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Item Display Entry", meta = (BindWidget))
	TObjectPtr<UTextBlock> AmountText;

	UPROPERTY(BlueprintReadOnly, Category = "Item Display Entry")
	TObjectPtr<UItemEntryObject> ItemObject;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

};
