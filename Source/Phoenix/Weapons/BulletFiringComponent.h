// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "BulletFiringComponent.generated.h"

class UBulletFiringData;
class UPhoenixAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FFireBulletQueueInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 AmountToFire;

	UPROPERTY(BlueprintReadWrite)
	bool bRollToHit;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UBulletFiringData> BulletFiringData;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UPhoenixAbilitySystemComponent> Shooter;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UPhoenixAbilitySystemComponent> Target;

	FFireBulletQueueInfo()
	{
		AmountToFire = 1;
		bRollToHit = true;
		BulletFiringData = nullptr;
		Shooter = nullptr;
		Target = nullptr;
	}
};

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PHOENIX_API UBulletFiringComponent : public UArrowComponent
{
	GENERATED_BODY()

public:

	UBulletFiringComponent();

	UFUNCTION(BlueprintCallable, Category = "Bullet Firing Component")
	void QueueAndFireBullets(const FFireBulletQueueInfo& QueueInfo);

private:

	void FireQueuedBullet();
	void FireBullet();
	
	FVector CalculateShotDirection();

	FTimerHandle RefireTimerHandle;

	FFireBulletQueueInfo CurrentQueue;
	
};
