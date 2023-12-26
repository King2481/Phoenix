// Created by Bruce Crum.


#include "Phoenix/Weapons/Projectiles/ImpactProjectile.h"
#include "Phoenix/Abilities/PhoenixAbilitySystemComponent.h"
#include "Phoenix/GameFramework/Damage/DamageCalculationType.h"

#include "Components/SphereComponent.h"

AImpactProjectile::AImpactProjectile()
{
	CollisionComp = CreateOptionalDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->SetGenerateOverlapEvents(false);

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
			
			for (UDamageCalculationTypeBase* Calculation : Damage.DamageCalculationTypes)
			{
				TotalDamageFromSource += Calculation->CalculateDamage();
			}

			Info.AddDamageSource(FDamageInfo(TotalDamageFromSource, Damage.DamageType));
		}

		ABS->ModifyHealth(Info);
	}

	if (--RemainingBounces <= 0)
	{
		Destroy();
	}
}