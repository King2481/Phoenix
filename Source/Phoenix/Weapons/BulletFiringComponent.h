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
	int32 CritDie;

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
		CritDie = 20;
		bRollToHit = true;
		BulletFiringData = nullptr;
		Shooter = nullptr;
		Target = nullptr;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShotsFiredDelegate);

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

	UPROPERTY(BlueprintAssignable)
	FOnShotsFiredDelegate OnShotsFiredDelegate;

private:

	void FireQueuedBullet();
	void FireBullet();
	
	FVector CalculateShotDirection();

	FTimerHandle RefireTimerHandle;

	FFireBulletQueueInfo CurrentQueue;
	
};
