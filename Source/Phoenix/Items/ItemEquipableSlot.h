// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemEquipableSlot.generated.h"

/**
 * 
 */
UCLASS()
class PHOENIX_API UItemEquipableSlot : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UItemEquipableSlot();
	
	// What is the display text for is this category displayed in the UI?
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Equipable Slot")
	FText DisplayName;
};
