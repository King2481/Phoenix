// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FactionInfo.generated.h"

/**
 * 
 */
UCLASS()
class PHOENIX_API UFactionInfo : public UDataAsset
{
	GENERATED_BODY()

public:

	UFactionInfo();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Faction Info")
	FText FactionName;
	
};
