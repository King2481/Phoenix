// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "GameplayTagContainer.h"
#include "AbilityTypes.generated.h"

class UPhoenixDamageType;
class UPhoenixAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FDamageInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 ChangeAmount;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UPhoenixDamageType> DamageType;

	FDamageInfo()
	{
		ChangeAmount = 0;
		DamageType = nullptr;
	}

};

USTRUCT(BlueprintType)
struct FModifyHealthInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<FDamageInfo> DamageSources;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FGameplayTagContainer DamageTagContainer;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TObjectPtr<UPhoenixAbilitySystemComponent> EffectedFrom;

	FModifyHealthInfo()
	{
		DamageTagContainer = FGameplayTagContainer();
		EffectedFrom = nullptr;
	}

	FModifyHealthInfo(const FGameplayTagContainer& InContainer)
	{
		DamageTagContainer = InContainer;
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