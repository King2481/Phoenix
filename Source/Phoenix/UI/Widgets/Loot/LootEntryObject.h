// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Phoenix/Items/InventoryTypes.h" //FInventoryItem 
#include "LootEntryObject.generated.h"

/**
 * 
 */
UCLASS()
class PHOENIX_API ULootEntryObject : public UObject
{
	GENERATED_BODY()

public:

	ULootEntryObject();

	UPROPERTY(BlueprintReadOnly, Category = "Loot Entry Object")
	FInventoryItem StoredItem;
	
};
