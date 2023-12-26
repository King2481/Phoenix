// Created by Bruce Crum.


#include "Phoenix/GameFramework/PhoenixGameplayStatics.h"
#include "Phoenix/GameFramework/Damage/DamageCalculationType.h"
#include "Phoenix/Weapons/Projectiles/ProjectileBase.h"

int32 UPhoenixGameplayStatics::RollDice(const TArray<FDiceRollInfo>& InDiceRoll)
{
	int32 Result = 0;

	for (auto& Dice : InDiceRoll)
	{
		for (int i = 0; i < Dice.RollAmount; i++)
		{
			Result += FMath::RandRange(1, int32(Dice.DiceType));
		}
	}

	return Result;
}

int32 UPhoenixGameplayStatics::CalculateDamageRoll(const TArray<UDamageCalculationTypeBase*> Calculations)
{
	int32 Result = 0;

	for (auto& Calculation : Calculations)
	{
		if (Calculation)
		{
			Result += Calculation->CalculateDamage();
		}
	}

	return Result;
}

AProjectileBase* UPhoenixGameplayStatics::SpawnProjectile(const UObject* WorldContextObject, const FProjectileSpawnInfo& SpawnInfo)
{
	if (UWorld* World = WorldContextObject ? WorldContextObject->GetWorld() : nullptr)
	{
		if (IsValid(SpawnInfo.ProjectileToSpawn))
		{
			const auto SpawnTransform = FTransform(SpawnInfo.SpawnDirection.Rotation(), SpawnInfo.SpawnLocation);

			if (const auto Projectile = World->SpawnActorDeferred<AProjectileBase>(SpawnInfo.ProjectileToSpawn, SpawnTransform, SpawnInfo.Owner, SpawnInfo.Instigator))
			{
				Projectile->InitProjectile(SpawnInfo.ProjectileProperties);
				UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);

				return Projectile;
			}
		}
	}

	return nullptr;
}