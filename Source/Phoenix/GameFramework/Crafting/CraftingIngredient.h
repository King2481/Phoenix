// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CraftingIngredient.generated.h"

class UItemSubCategory;
struct FInventoryItem;

/**
 * 
 */
UCLASS(Abstract, Blueprintable, EditInlineNew)
class PHOENIX_API UCraftingIngredientBase : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bConsumeItemOnCraft = true;
	
};

UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Requires Specific Item"))
class UCraftingIngredientItem : public UCraftingIngredientBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<FInventoryItem> RequiredItems;

};

UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Requires Any Type"))
class UCraftingIngredientAnyType : public UCraftingIngredientBase
{
	GENERATED_BODY()

public:
	 
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<UItemSubCategory> RequiredSubCategory = nullptr;
};
