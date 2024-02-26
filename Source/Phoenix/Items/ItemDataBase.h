// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataBase.generated.h"

class UItemCategory;
class UItemSubCategory;
class UItemQuality;

/**
 * 
 */
UCLASS(BlueprintType)
class PHOENIX_API UItemDataBase : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UItemDataBase();

	// What is the item's name?
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Base")
	FText ItemName;

	// What is the item's description?
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Base")
	FText ItemDescription;

	// Can this item be stacked?
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Base")
	bool bStackable;

	// What is the maximum amount of this item that is allowed?
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Base", meta = (EditCondition = "bStackable", EditConditionHides, UIMin = "2", ClampMin = "2"))
	int32 MaximumAmount;

	// What category of item is this?
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Base")
	TObjectPtr<UItemCategory> ItemCategory;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Base")
	TObjectPtr<UItemSubCategory> ItemSubCategory;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Base")
	TObjectPtr<UItemQuality> ItemQuality;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Base")
	TObjectPtr<UTexture2D> InventoryItemTexture;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Base")
	bool bPickpocketable;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Base", meta = (EditCondition = "bPickpocketable", EditConditionHides))
	uint8 PickpocketDifficultyClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Base", meta = (EditCondition = "bPickpocketable", EditConditionHides))
	uint8 PickpocketCaughtSaveDifficultyClass;
};
