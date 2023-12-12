// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ReputationInfo.generated.h"

class UFactionInfo;

USTRUCT(BlueprintType)
struct FFactionReputation
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UFactionInfo> Faction;

	UPROPERTY(BlueprintReadWrite)
	float Modifier;

	FFactionReputation()
	{
		Faction = nullptr;
		Modifier = 0.0f;
	}
};


/**
 * 
 */
UCLASS()
class PHOENIX_API UReputationInfo : public UDataAsset
{
	GENERATED_BODY()

public:

	UReputationInfo();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Reputation Info")
	TArray<FFactionReputation> FactionModifiers;
	
};
