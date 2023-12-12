// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InteractionData.generated.h"

class UMouseIconSet;
class UPhoenixGameplayAbility;

/**
 * 
 */
UCLASS(BlueprintType)
class PHOENIX_API UInteractionData : public UDataAsset
{
	GENERATED_BODY()

public:

	UInteractionData();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Interaction Data")
	FText LocalizedName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Interaction Data")
	TSoftClassPtr<UPhoenixGameplayAbility> InteractionAbility;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Interaction Data")
	TObjectPtr<UMouseIconSet> MouseIconSet;
	
};
