// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "PhoenixTypes.h"
#include "PhoenixGameplayStatics.generated.h"

class UExplosionData;

USTRUCT(BlueprintType)
struct FInteractionInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AActor> InstigatingActor;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AActor> TargetActor;

	FInteractionInfo()
	{
		InstigatingActor = nullptr;
		TargetActor = nullptr;
	}

	FInteractionInfo(AActor* InInstigatingActor, AActor* InTargetActor)
	{
		InstigatingActor = InInstigatingActor;
		TargetActor = InTargetActor;
	}
};

USTRUCT(BlueprintType)
struct FDiceRollToBeatResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	bool bSuccessfullyPassed;

	UPROPERTY(BlueprintReadOnly)
	int32 AmountRolled;

	FDiceRollToBeatResult()
	{
		bSuccessfullyPassed = false;
		AmountRolled = 0;
	}

	FDiceRollToBeatResult(bool bInSuccessfullyPassed, int32 InAmountRolled)
	{
		bSuccessfullyPassed = bInSuccessfullyPassed;
		AmountRolled = InAmountRolled;
	}
};

/**
 * 
 */
UCLASS()
class PHOENIX_API UPhoenixGameplayStatics : public UGameplayStatics
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Phoenix Gameplay Statics")
	static int32 RollDice(const TArray<FDiceRollInfo>& InDiceRoll);

	UFUNCTION(BlueprintCallable, Category = "Phoenix Gameplay Statics")
	static FDiceRollToBeatResult RollDiceToBeat(const TArray<FDiceRollInfo>& InDiceRoll, const int32 NumberToBeat);
	
	UFUNCTION(BlueprintPure, Category = "Phoenix Gameplay Statics")
	static int32 CalculateDamageRoll(const TArray<UDamageCalculationTypeBase*> Calculations);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Phoenix Gameplay Statics")
	static AProjectileBase* SpawnProjectile(const UObject* WorldContextObject, const FProjectileSpawnInfo& SpawnInfo);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Phoenix Gameplay Statics")
	static void Explode(const UObject* WorldContextObject, AActor* ExplodingActor, const FVector& Location, UExplosionData* ExplosionData);

};
