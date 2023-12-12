// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "AbilityTypes.generated.h"

class UPhoenixDamageType;
class UPhoenixAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FModifyHealthInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 ChangeAmount;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UPhoenixDamageType> DamageType;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TObjectPtr<UPhoenixAbilitySystemComponent> EffectedFrom;

	FModifyHealthInfo()
	{
		ChangeAmount = 0;
		DamageType = nullptr;
		EffectedFrom = nullptr;
	}

	FModifyHealthInfo(const int32 InChangeAmount, TSubclassOf<UPhoenixDamageType> InDamageType)
	{
		ChangeAmount = InChangeAmount;
		DamageType = InDamageType;
		EffectedFrom = nullptr;
	}
};

USTRUCT(BlueprintType)
struct FTargetData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<UPhoenixAbilitySystemComponent>> Targets;

	FTargetData()
	{
	
	}

	FTargetData(UPhoenixAbilitySystemComponent* InTarget)
	{
		Targets.AddUnique(InTarget);
	}
};