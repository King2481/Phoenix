// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EquipmentSlotLayout.generated.h"

class UItemEquipableSlot;

/**
 * 
 */
UCLASS()
class PHOENIX_API UEquipmentSlotLayout : public UDataAsset
{
	GENERATED_BODY()

public:

	UEquipmentSlotLayout();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Equipment Slot Layout")
	TArray<TObjectPtr<UItemEquipableSlot>> AcceptableSlots;
	
};
