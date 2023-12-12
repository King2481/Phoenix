// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "PhoenixTypes.generated.h"

class UPhoenixDamageType;
class UPhoenixAbilitySystemComponent;
class UDamageCalculationTypeBase;
class AProjectileBase;

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
struct FDamageInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UPhoenixDamageType> DamageType;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Instanced)
	TArray<TObjectPtr<UDamageCalculationTypeBase>> DamageCalculationTypes;

	FDamageInfo()
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
	TObjectPtr<AActor> Owner;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TObjectPtr<APawn> Instigator;

	FProjectileSpawnInfo()
	{
		ProjectileToSpawn = nullptr;
		SpawnDirection = FVector::ZeroVector;
		SpawnLocation = FVector::ZeroVector;
		Owner = nullptr;
		Instigator = nullptr;
	}

	FProjectileSpawnInfo(TSubclassOf<AProjectileBase> InProjectileClass, const FVector& InShotDirection, const FVector& InSpawnLocation, AActor* InOwner, APawn* InInstigator)
	{
		ProjectileToSpawn = InProjectileClass;
		SpawnDirection = InShotDirection;
		SpawnLocation = InSpawnLocation;
		Owner = InOwner;
		Instigator = InInstigator;
	}
};