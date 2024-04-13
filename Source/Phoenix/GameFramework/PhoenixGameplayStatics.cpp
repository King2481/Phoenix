// Created by Bruce Crum.


#include "Phoenix/GameFramework/PhoenixGameplayStatics.h"
#include "Phoenix/GameFramework/Damage/DamageCalculationType.h"
#include "Phoenix/GameFramework/Explosions/ExplosionData.h"
#include "Phoenix/GameFramework/Explosions/Launchable.h"
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

void UPhoenixGameplayStatics::Explode(const UObject* WorldContextObject, const FExplosionInfo& ExplosionInfo)
{
	// Damage
	{
		if (UWorld* World = WorldContextObject->GetWorld())
		{
			TArray<FHitResult> Hits;

			FCollisionQueryParams Params;
			Params.AddIgnoredActor(ExplosionInfo.ExplodingActor);
			Params.bTraceComplex = false;

			const auto ExploderABS = ExplosionInfo.ExplodingActor->FindComponentByClass<UPhoenixAbilitySystemComponent>();

			if (World->SweepMultiByChannel(Hits, ExplosionInfo.Location, ExplosionInfo.Location, FQuat::Identity, ECC_Explosion, FCollisionShape::MakeSphere(ExplosionInfo.ExplosionData->ExplosionOuterRadius), Params))
			{
				for (const auto& Hit : Hits)
				{
					if (const auto TargetABS = Hit.GetActor()->FindComponentByClass<UPhoenixAbilitySystemComponent>())
					{
						const float Distance = (Hit.ImpactPoint - ExplosionInfo.Location).Size();
						const float Alpha = (Distance - ExplosionInfo.ExplosionData->ExplosionInnerRadius) / (ExplosionInfo.ExplosionData->ExplosionOuterRadius - ExplosionInfo.ExplosionData->ExplosionInnerRadius);
						const float DamageFalloff = ExplosionInfo.ExplosionData->DamageFalloffCurve.GetRichCurveConst()->Eval(Alpha);
						const int32 Damage = FMath::Lerp<int32>(ExplosionInfo.ExplosionData->ExplosionInnerDamage, ExplosionInfo.ExplosionData->ExplosionOuterDamage, DamageFalloff);

						FModifyHealthInfo Info;
						Info.AddDamageSource(FDamageInfo(Damage, ExplosionInfo.ExplosionData->ExplosionDamageTypeClass, Hit.ImpactPoint, false));
						Info.CausedBy = ExploderABS;

						TargetABS->ModifyHealth(Info);
					}

					if (const auto Launchable = Cast<ILaunchable>(Hit.GetActor()))
					{
						if (ILaunchable::Execute_CanLaunch(Hit.GetActor()))
						{
							if (UPrimitiveComponent* Comp = ILaunchable::Execute_GetPrimitiveComponentForLaunch(Hit.GetActor()))
							{
								const float Distance = (Hit.ImpactPoint - ExplosionInfo.Location).Size();
								const float Alpha = (Distance - ExplosionInfo.ExplosionData->ExplosionInnerForceImpulseRadius) / (ExplosionInfo.ExplosionData->ExplosionOuterForceImpulseRadius - ExplosionInfo.ExplosionData->ExplosionInnerForceImpulseRadius);
								const float Falloff = ExplosionInfo.ExplosionData->ImpulseFalloffCurve.GetRichCurveConst()->Eval(Alpha);
								const float LaunchStrength = FMath::Lerp<float>(ExplosionInfo.ExplosionData->ExplosionInnerForceImpulseStrength, ExplosionInfo.ExplosionData->ExplosionOuterForceImpulseStrength, Falloff);

								Comp->AddImpulse(-Hit.Normal * LaunchStrength, Hit.BoneName);
							}
						}
					}

#if !UE_BUILD_SHIPPING
					if (CvarDebugExplosion.GetValueOnGameThread() > 0)
					{
						UKismetSystemLibrary::DrawDebugSphere(WorldContextObject, Hit.ImpactPoint, 50.0f, 12, FColor::Blue, 5.0f, 1.0f);
					}
#endif
				}
			}

			if (CvarDebugExplosion.GetValueOnGameThread() > 1)
			{
				UKismetSystemLibrary::DrawDebugSphere(WorldContextObject, ExplosionInfo.Location, ExplosionInfo.ExplosionData->ExplosionInnerForceImpulseRadius, 12, FColor::Green, 5.0f, 1.0f);
				UKismetSystemLibrary::DrawDebugSphere(WorldContextObject, ExplosionInfo.Location, ExplosionInfo.ExplosionData->ExplosionOuterForceImpulseRadius, 12, FColor::Purple, 5.0f, 1.0f);
			}
		}
	}

	// FX
	{
		if (ExplosionInfo.ExplosionData->ExplosionSound)
		{
			UGameplayStatics::PlaySoundAtLocation(WorldContextObject, ExplosionInfo.ExplosionData->ExplosionSound, ExplosionInfo.Location);
		}

		if (ExplosionInfo.ExplosionData->ExplosionFX)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(WorldContextObject, ExplosionInfo.ExplosionData->ExplosionFX, ExplosionInfo.Location);
		}

		if (ExplosionInfo.ExplosionData->CameraShakeData.ExplosionCameraShakeClass)
		{
			UGameplayStatics::PlayWorldCameraShake(WorldContextObject, 
				ExplosionInfo.ExplosionData->CameraShakeData.ExplosionCameraShakeClass,
				ExplosionInfo.Location, ExplosionInfo.ExplosionData->CameraShakeData.ExplosionCameraShakeInnerRadius,
				ExplosionInfo.ExplosionData->CameraShakeData.ExplosionCameraShakeOuterRadius, 1.0f, true);
		}
	}

	// AI
	{
		// Note: So in order for a pawn to "hear" an explosion, the instigator can NOT be nullptr, if this were a commercial project,
		// I'd probably want to look into doing an engine modification so it allows pawns to hear things from unknown sources.
		ExplosionInfo.ExplodingActor->MakeNoise(1.0f, ExplosionInfo.Instigator, ExplosionInfo.Location, 0.0f, FName("Explosion"));
	}

#if !UE_BUILD_SHIPPING
	if (CvarDebugExplosion.GetValueOnGameThread() > 0)
	{
		UKismetSystemLibrary::DrawDebugSphere(WorldContextObject, ExplosionInfo.Location, ExplosionInfo.ExplosionData->ExplosionInnerRadius, 12, FColor::Red, 5.0f, 1.0f);
		UKismetSystemLibrary::DrawDebugSphere(WorldContextObject, ExplosionInfo.Location, ExplosionInfo.ExplosionData->ExplosionOuterRadius, 12, FColor::Yellow, 5.0f, 1.0f);
	}
#endif
}