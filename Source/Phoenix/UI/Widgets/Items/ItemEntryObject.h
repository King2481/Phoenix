// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Phoenix/Items/InventoryTypes.h" //FInventoryItem 
#include "ItemEntryObject.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PHOENIX_API UItemEntryObject : public UObject
{
	GENERATED_BODY()

public:

	UItemEntryObject();

	UPROPERTY(BlueprintReadOnly, Category = "Item Entry Object")
	FInventoryItem StoredItem;
	
};
