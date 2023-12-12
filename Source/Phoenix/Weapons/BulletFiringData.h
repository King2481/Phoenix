// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BulletFiringData.generated.h"

class AProjectileBase;
struct FDamageInfo;

/**
 * 
 */
UCLASS()
class PHOENIX_API UBulletFiringData : public UDataAsset
{
	GENERATED_BODY()

public:

	UBulletFiringData();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Ammo")
	TSubclassOf<AProjectileBase> ProjectileToSpawn;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Ammo")
	TArray<FDamageInfo> BulletDamageInfo;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Ammo")
	uint8 TotalShots;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Ammo", meta = (ClampMin = "1.0", UIMin = "1.0"))
	float RateOfFire;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Ammo", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxSpreadInDegrees;

	UFUNCTION(BlueprintPure, Category = "Bullet Firing Data")
	float GetFriendlyRateOfFireForTimer() const { return 60.0f / RateOfFire; }
};
