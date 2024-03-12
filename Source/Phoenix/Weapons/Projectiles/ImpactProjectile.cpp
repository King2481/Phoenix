// Created by Bruce Crum.


#include "Phoenix/Weapons/Projectiles/ImpactProjectile.h"
#include "Phoenix/Abilities/PhoenixAbilitySystemComponent.h"
#include "Phoenix/GameFramework/Damage/DamageCalculationType.h"
#include "Phoenix/FX/SurfaceReactionComponent.h"
#include "Phoenix/GameFramework/Explosions/Launchable.h"

#include "Components/SphereComponent.h"

AImpactProjectile::AImpactProjectile()
{
	CollisionComp = CreateOptionalDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->SetGenerateOverlapEvents(false);

	SurfaceReactionComponent = CreateOptionalDefaultSubobject<USurfaceReactionComponent>(TEXT("Surface Reaction"));

	RootComponent = CollisionComp;
}

void AImpactProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionComp->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
}

void AImpactProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CollisionComp->OnComponentHit.RemoveDynamic(this, &ThisClass::OnHit);

	Super::EndPlay(EndPlayReason);
}

void AImpactProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (const auto ABS = OtherActor->GetComponentByClass<UPhoenixAbilitySystemComponent>())
	{
		FModifyHealthInfo Info;

		if (GetInstigator())
		{
			Info.CausedBy = GetInstigator()->FindComponentByClass<UPhoenixAbilitySystemComponent>();
		}

		for (FDamageCalculationInfo Damage : DamageCalculations)
		{
			int32 TotalDamageFromSource = 0;

			const bool bWasCrit = FMath::RandRange(0, 20) >= CritDie;
			
			for (UDamageCalculationTypeBase* Calculation : Damage.DamageCalculationTypes)
			{
				TotalDamageFromSource += Calculation->CalculateDamage();
			}

			Info.AddDamageSource(FDamageInfo(TotalDamageFromSource, Damage.DamageType, GetActorLocation(), bWasCrit));
		}

		ABS->ModifyHealth(Info);
	}

	if (const auto Launchable = Cast<ILaunchable>(Hit.GetActor()))
	{
		if (ILaunchable::Execute_CanLaunch(Hit.GetActor()))
		{
			if (UPrimitiveComponent* Comp = ILaunchable::Execute_GetPrimitiveComponentForLaunch(Hit.GetActor()))
			{
				const float LaunchStrength = 2500.0f;

				if (Hit.BoneName != NAME_None)
				{
					Comp->AddImpulse(-Hit.Normal * LaunchStrength, Hit.BoneName);
				}
			}
		}
	}

	SurfaceReactionComponent->PlaySurfaceReactionFromHitResult(Hit);

	if (--RemainingBounces <= 0)
	{
		Destroy();
	}
}