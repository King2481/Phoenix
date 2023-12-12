// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemQuality.generated.h"

/**
 * 
 */
UCLASS()
class PHOENIX_API UItemQuality : public UDataAsset
{
	GENERATED_BODY()

public:

	UItemQuality();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Quality")
	FText DisplayText;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Quality")
	FLinearColor DisplayColor;
	
};
