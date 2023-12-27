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

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FVector HitLocation;


	FDamageInfo()
	{
		ChangeAmount = 0;
		DamageType = nullptr;
		HitLocation = FVector::ZeroVector;
	}

	FDamageInfo(int32 InChangeAmount, TSubclassOf<UPhoenixDamageType> InDamageType, const FVector& InHitLocation)
	{
		ChangeAmount = InChangeAmount;
		DamageType = InDamageType;
		HitLocation = InHitLocation;
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
	TObjectPtr<UPhoenixAbilitySystemComponent> CausedBy;

	FModifyHealthInfo()
	{
		DamageTagContainer = FGameplayTagContainer();
		CausedBy = nullptr;
	}

	void AddDamageSource(const FDamageInfo& InSource)
	{
		DamageSources.Add(InSource);
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