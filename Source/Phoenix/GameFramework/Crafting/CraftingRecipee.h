// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Phoenix/Items/InventoryTypes.h"
#include "CraftingRecipee.generated.h"

class UCraftingIngredientBase;

/**
 * 
 */
UCLASS()
class PHOENIX_API UCraftingRecipee : public UDataAsset
{
	GENERATED_BODY()

public:

	UCraftingRecipee();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Crafting Recipee")
	FInventoryItem ProducesItem;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Instanced, Category = "Crafting Recipee")
	TArray<TObjectPtr<UCraftingIngredientBase>> RequiredItems;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Crafting Recipee")
	bool bIsFieldCraftable;
};
