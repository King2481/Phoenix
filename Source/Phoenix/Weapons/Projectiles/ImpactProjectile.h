// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Phoenix/Weapons/Projectiles/ProjectileBase.h"
#include "ImpactProjectile.generated.h"

class USphereComponent;

/**
 * 
 */
UCLASS()
class PHOENIX_API AImpactProjectile : public AProjectileBase
{
	GENERATED_BODY()

public:

	AImpactProjectile();

protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/* Collision shape component */
	UPROPERTY(VisibleDefaultsOnly, Category = "Impact Projectile")
	USphereComponent* CollisionComp;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	
};
