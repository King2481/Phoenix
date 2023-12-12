// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemCategory.generated.h"

/**
 * 
 */
UCLASS()
class PHOENIX_API UItemCategory : public UDataAsset
{
	GENERATED_BODY()

public:

	UItemCategory();

	// What is the display text for is this category displayed in the UI?
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Category")
	FText DisplayName;
	
};

UCLASS()
class PHOENIX_API UItemSubCategory : public UItemCategory
{
	GENERATED_BODY()


};
