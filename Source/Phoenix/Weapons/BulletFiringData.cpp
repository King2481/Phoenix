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