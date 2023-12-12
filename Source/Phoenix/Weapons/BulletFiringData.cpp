// Created by Bruce Crum.


#include "Phoenix/Weapons/BulletFiringData.h"

UBulletFiringData::UBulletFiringData()
{
	ProjectileToSpawn = nullptr;
	TotalShots = 1;
	RateOfFire = 750.0f;
	MaxSpreadInDegrees = 0.0f;
}