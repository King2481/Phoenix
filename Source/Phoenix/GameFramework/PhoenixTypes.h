// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "PhoenixTypes.generated.h"

class UPhoenixDamageType;
class UPhoenixAbilitySystemComponent;
class UDamageCalculationTypeBase;
class AProjectileBase;
class UCameraShakeBase;

UENUM(BlueprintType)
enum class EDiceType : uint8
{
    D0 = 0      UMETA(Hidden),
    D4 = 4      UMETA(DisplayName = "D4"),
    D6 = 6      UMETA(DisplayName = "D6"),
    D8 = 8      UMETA(DisplayName = "D8"),
    D10 = 10    UMETA(DisplayName = "D10"),
	D12 = 12    UMETA(DisplayName = "D12"),
    D20 = 20    UMETA(DisplayName = "D20"),
    D100 = 100  UMETA(DisplayName = "D100")
};

USTRUCT(BlueprintType)
struct FDiceRollInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	uint8 RollAmount;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	EDiceType DiceType;

	FDiceRollInfo()
	{
		RollAmount = 1;
		DiceType = EDiceType::D20;
	}

	FDiceRollInfo(const uint8 InRollAmount, const EDiceType InDiceType)
	{
		RollAmount = InRollAmount;
		DiceType = InDiceType;
	}

	FDiceRollInfo(const EDiceType InDiceType)
	{
		RollAmount = 1;
		DiceType = InDiceType;
	}
};

USTRUCT(BlueprintType)
struct FDamageCalculationInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UPhoenixDamageType> DamageType;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Instanced)
	TArray<TObjectPtr<UDamageCalculationTypeBase>> DamageCalculationTypes;

	FDamageCalculationInfo()
	{
		DamageType = nullptr;
	}
};

USTRUCT(BlueprintType)
struct FOnDeathInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TObjectPtr<AActor> Victim;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TObjectPtr<UPhoenixAbilitySystemComponent> KillerABS;

	FOnDeathInfo()
	{
		Victim = nullptr;
		KillerABS = nullptr;
	}

	FOnDeathInfo(AActor* InVictim, UPhoenixAbilitySystemComponent* InKillerABS)
	{
		Victim = InVictim;
		KillerABS = InKillerABS;
	}
};

UENUM(BlueprintType)
enum class ERollType : uint8
{
	Normal        UMETA(DisplayName = "Normal"),
	Advantage     UMETA(DisplayName = "Advantage"),
	Disadvantage  UMETA(DisplayName = "Disadvantage")
};

USTRUCT(BlueprintType)
struct FDifficultyClassInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	uint8 DifficultyClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ERollType RollType;

	FDifficultyClassInfo()
	{
		DifficultyClass = 0;
		RollType = ERollType::Normal;
	}

	bool operator>=(const uint8 Other) const
	{
		return DifficultyClass >= Other;
	}
};

USTRUCT(BlueprintType)
struct FProjectileProperties
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float ProjectileSpeed;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float ProjectileLifeSpan;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bShouldBounce;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (EditCondition = "bShouldBounce", EditConditionHides))
	float Bounciness;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (EditCondition = "bShouldBounce", EditConditionHides, ClampMin = "0", UIMin = "0"))
	int32 MaxBounces;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float GravityScale;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<FDamageCalculationInfo> DamageCalculations;

	FProjectileProperties()
	{
		ProjectileSpeed = 4500.0f;
		ProjectileLifeSpan = 3.0f;
		bShouldBounce = false;
		Bounciness = 0.4f;
		MaxBounces = 1;
		GravityScale = 0.0f;
	}
};

USTRUCT(BlueprintType)
struct FProjectileSpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<AProjectileBase> ProjectileToSpawn;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FVector SpawnDirection;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FVector SpawnLocation;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FProjectileProperties ProjectileProperties;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TObjectPtr<AActor> Owner;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TObjectPtr<APawn> Instigator;

	FProjectileSpawnInfo()
	{
		ProjectileToSpawn = nullptr;
		SpawnDirection = FVector::ZeroVector;
		SpawnLocation = FVector::ZeroVector;
		ProjectileProperties = FProjectileProperties();
		Owner = nullptr;
		Instigator = nullptr;
	}
};

USTRUCT(BlueprintType)
struct FCameraShakeData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UCameraShakeBase> ExplosionCameraShakeClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float ExplosionCameraShakeInnerRadius;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float ExplosionCameraShakeOuterRadius;

	FCameraShakeData()
	{
		ExplosionCameraShakeClass = nullptr;
		ExplosionCameraShakeInnerRadius = 100.0f;
		ExplosionCameraShakeOuterRadius = 1000.0f;
	}
};