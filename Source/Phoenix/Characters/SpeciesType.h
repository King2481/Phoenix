// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SpeciesType.generated.h"

/**
 * 
 */
UCLASS()
class PHOENIX_API USpeciesType : public UDataAsset
{
	GENERATED_BODY()

public:

	USpeciesType();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Species Type")
	FText SpeciesName;
	
};
