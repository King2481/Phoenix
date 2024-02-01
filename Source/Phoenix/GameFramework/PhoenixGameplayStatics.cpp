// Created by Bruce Crum.


#include "Phoenix/GameFramework/PhoenixGameplayStatics.h"
#include "Phoenix/GameFramework/Damage/DamageCalculationType.h"
#include "Phoenix/GameFramework/Explosions/ExplosionData.h"
#include "Phoenix/Weapons/Projectiles/ProjectileBase.h"
#include "Phoenix/Engine/GameTraceChannels.h"
#include "Phoenix/Abilities/PhoenixAbilitySystemComponent.h"

#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

#if !UE_BUILD_SHIPPING
static TAutoConsoleVariable<int32> CvarDebugExplosion(TEXT("DebugExplosions"), 0, TEXT("Visualise Explosion Info"));

#endif

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

FDiceRollToBeatResult UPhoenixGameplayStatics::RollDiceToBeat(const TArray<FDiceRollInfo>& InDiceRoll, const int32 NumberToBeat)
{
	const int32 AmountRolled = RollDice(InDiceRoll);

	return FDiceRollToBeatResult(AmountRolled >= NumberToBeat, AmountRolled);
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

void UPhoenixGameplayStatics::Explode(const UObject* WorldContextObject, AActor* ExplodingActor, const FVector& Location, UExplosionData* ExplosionData)
{
	// Damage
	{
		if (UWorld* World = WorldContextObject->GetWorld())
		{
			if (const auto ABS = ExplodingActor->FindComponentByClass<UPhoenixAbilitySystemComponent>())
			{
				TArray<FHitResult> Hits;

				FCollisionQueryParams Params;
				Params.AddIgnoredActor(ExplodingActor);
				Params.bTraceComplex = false;

				if (World->SweepMultiByChannel(Hits, Location, Location + FVector(1.0f), FQuat::Identity, ECC_Explosion, FCollisionShape::MakeSphere(ExplosionData->ExplosionOuterRadius), Params))
				{
					for (const auto& Hit : Hits)
					{
						if (const auto TargetABS = Hit.GetActor()->FindComponentByClass<UPhoenixAbilitySystemComponent>())
						{
							const float Distance = (Hit.ImpactPoint - Location).Size();
							const float Alpha = (Distance - ExplosionData->ExplosionInnerRadius) / (ExplosionData->ExplosionOuterRadius - ExplosionData->ExplosionInnerRadius);
							const float DamageFalloff = ExplosionData->DamageFalloffCurve.GetRichCurveConst()->Eval(Alpha);
							const int32 Damage = FMath::Lerp<int32>(ExplosionData->ExplosionInnerDamage, ExplosionData->ExplosionOuterDamage, DamageFalloff);

							FModifyHealthInfo Info;
							Info.AddDamageSource(FDamageInfo(Damage, ExplosionData->ExplosionDamageTypeClass, Hit.ImpactPoint, false));
							Info.CausedBy = ABS;

							TargetABS->ModifyHealth(Info);
						}

#if !UE_BUILD_SHIPPING
						if (CvarDebugExplosion.GetValueOnGameThread() > 0)
						{
							UKismetSystemLibrary::DrawDebugSphere(WorldContextObject, Hit.ImpactPoint, 50.0f, 12, FColor::Blue, 5.0f, 1.0f);
						}
#endif
					}
				}
			}
		}
	}

	// FX
	{
		if (ExplosionData->ExplosionSound)
		{
			UGameplayStatics::PlaySoundAtLocation(WorldContextObject, ExplosionData->ExplosionSound, Location);
		}

		if (ExplosionData->ExplosionFX)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(WorldContextObject, ExplosionData->ExplosionFX, Location);
		}

		if (ExplosionData->CameraShakeData.ExplosionCameraShakeClass)
		{
			UGameplayStatics::PlayWorldCameraShake(WorldContextObject, 
				ExplosionData->CameraShakeData.ExplosionCameraShakeClass, 
				Location, ExplosionData->CameraShakeData.ExplosionCameraShakeInnerRadius, 
				ExplosionData->CameraShakeData.ExplosionCameraShakeOuterRadius, 1.0f, true);
		}
	}

#if !UE_BUILD_SHIPPING
	if (CvarDebugExplosion.GetValueOnGameThread() > 0)
	{
		UKismetSystemLibrary::DrawDebugSphere(WorldContextObject, Location, ExplosionData->ExplosionInnerRadius, 12, FColor::Red, 5.0f, 1.0f);
		UKismetSystemLibrary::DrawDebugSphere(WorldContextObject, Location, ExplosionData->ExplosionOuterRadius, 12, FColor::Yellow, 5.0f, 1.0f);
	}
#endif
}