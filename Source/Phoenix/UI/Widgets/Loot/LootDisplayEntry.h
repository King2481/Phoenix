// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Phoenix/UI/Widgets/ToolTipWidget.h"
#include "Blueprint/IUserObjectListEntry.h" // IUserObjectListEntry
#include "LootDisplayEntry.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class PHOENIX_API ULootDisplayEntry : public UToolTipWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:

	ULootDisplayEntry(const FObjectInitializer& ObjectInitializer);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Loot Display Entry", meta = (BindWidget))
	TObjectPtr<UTextBlock> AmountText;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
};
