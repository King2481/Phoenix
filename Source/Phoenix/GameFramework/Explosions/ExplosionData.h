// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Phoenix/GameFramework/PhoenixTypes.h" // FCameraShakeData
#include "ExplosionData.generated.h"

class USoundBase;
class UPhoenixDamageType;
class UNiagaraSystem;
struct FRuntimeCurveFloat;

/**
 * 
 */
UCLASS()
class PHOENIX_API UExplosionData : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UExplosionData();

	///////////////////////////////////////////////////////////////////
	// Explosion Config

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Explosion Data")
	float ExplosionInnerRadius;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Explosion Data")
	float ExplosionOuterRadius;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Explosion Data")
	int32 ExplosionInnerDamage;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Explosion Data")
	int32 ExplosionOuterDamage;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Explosion Data")
	FRuntimeFloatCurve DamageFalloffCurve;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Explosion Data")
	TSubclassOf<UPhoenixDamageType> ExplosionDamageTypeClass;

	///////////////////////////////////////////////////////////////////
	// Camera Shake Config

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Explosion Data")
	FCameraShakeData CameraShakeData;

	///////////////////////////////////////////////////////////////////
	// FX

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Explosion Data")
	TObjectPtr<USoundBase> ExplosionSound;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Explosion Data")
	TObjectPtr<UNiagaraSystem> ExplosionFX;

	
};
