// Created by Bruce Crum.


#include "Phoenix/Weapons/BulletFiringData.h"

UBulletFiringData::UBulletFiringData()
{
	ProjectileToSpawn = nullptr;
	TotalShots = 1;
	ProjectileProperties = FProjectileProperties();
	RateOfFire = 750.0f;
	MaxSpreadInDegrees = 0.0f;
}

#if WITH_EDITOR

void UBulletFiringData::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (!ProjectileProperties.bShouldBounce && ProjectileProperties.MaxBounces != 1)
	{
		ProjectileProperties.MaxBounces = 1; // Ensure MaxBounces is only 1 when bShouldBounce is false.
	}
}

#endif