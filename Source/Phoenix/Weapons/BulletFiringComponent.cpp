// Created by Bruce Crum.


#include "Phoenix/Weapons/BulletFiringComponent.h"
#include "Phoenix/Weapons/BulletFiringData.h"
#include "Phoenix/GameFramework/PhoenixGameplayStatics.h"
#include "Phoenix/Abilities/PhoenixAbilitySystemComponent.h"

UBulletFiringComponent::UBulletFiringComponent()
{
	CurrentQueue = FFireBulletQueueInfo();
}

void UBulletFiringComponent::QueueAndFireBullets(const FFireBulletQueueInfo& QueueInfo)
{
	// TODO: We may need to do is firing check.
	// I cannot think of a situation where this function is called while the gun is currently firing
	// But just in case, we may need that check here.
	CurrentQueue = QueueInfo;

	FireQueuedBullet();
}

void UBulletFiringComponent::FireQueuedBullet()
{
	if (CurrentQueue.BulletFiringData)
	{
		FireBullet();

		--CurrentQueue.AmountToFire;
		if (CurrentQueue.AmountToFire > 0)
		{
			GetWorld()->GetTimerManager().SetTimer(RefireTimerHandle, this, &ThisClass::FireQueuedBullet, CurrentQueue.BulletFiringData->GetFriendlyRateOfFireForTimer());
		}
		else
		{
			CurrentQueue = FFireBulletQueueInfo();
		}
	}
}

void UBulletFiringComponent::FireBullet()
{
	if (CurrentQueue.BulletFiringData)
	{
		for (int i = 0; i < CurrentQueue.BulletFiringData->TotalShots; ++i)
		{
			// TOOD: Add Weapon Damage data if applicable. 

			auto SpawnInfo = FProjectileSpawnInfo();
			SpawnInfo.ProjectileToSpawn = CurrentQueue.BulletFiringData->ProjectileToSpawn;
			SpawnInfo.SpawnLocation = GetComponentLocation();
			SpawnInfo.SpawnDirection = CalculateShotDirection();
			SpawnInfo.ProjectileProperties = CurrentQueue.BulletFiringData->ProjectileProperties;
			SpawnInfo.ProjectileProperties.CritDie = CurrentQueue.CritDie;
			SpawnInfo.Owner = GetOwner();
			SpawnInfo.Instigator = GetOwner()->GetInstigator();

			UPhoenixGameplayStatics::SpawnProjectile(this, SpawnInfo);
		}

		OnShotsFiredDelegate.Broadcast();
	}
}

FVector UBulletFiringComponent::CalculateShotDirection()
{
	const AActor* TargetActor = CurrentQueue.Target->GetOwnerActor();
	const FBox TargetBounds = TargetActor->GetComponentsBoundingBox();

	if (CurrentQueue.bRollToHit)
	{
		FVector RandomOffset = FVector::ZeroVector;
		
		// Pass in through an initializer list, I didn't even know this existed!
		if (UPhoenixGameplayStatics::RollDiceToBeat({ FDiceRollInfo(EDiceType::D100) }, 50))
		{
			// If we missed a shot, pick a location outside the bounds of the character to shoot at.
			RandomOffset = FVector(
				FMath::FRandRange(-1.5f, 1.5f) * TargetBounds.GetExtent().X,
				FMath::FRandRange(-1.5f, 1.5f) * TargetBounds.GetExtent().Y,
				FMath::FRandRange(-1.5f, 1.5f) * TargetBounds.GetExtent().Z
			);
		}
	
		return ((TargetBounds.GetCenter() + RandomOffset) - GetComponentLocation()).GetSafeNormal();
	}
	else
	{
		// If it isn't a roll to hit, just fire it like a regular projectile in a Top Down Shooter.
		const FVector ForwardVector = (TargetBounds.GetCenter() - GetComponentLocation()).GetSafeNormal();
		const float ConeHalfAngle = FMath::DegreesToRadians(CurrentQueue.BulletFiringData->MaxSpreadInDegrees);
		FRandomStream WeaponRandomStream(FMath::Rand());

		return WeaponRandomStream.VRandCone(ForwardVector, ConeHalfAngle, ConeHalfAngle);
	}
}