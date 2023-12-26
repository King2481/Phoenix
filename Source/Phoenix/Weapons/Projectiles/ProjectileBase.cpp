// Created by Bruce Crum.


#include "Phoenix/Weapons/Projectiles/ProjectileBase.h"

#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetActorTickEnabled(false);
	
	SetLifeSpan(3.0f);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
}

void AProjectileBase::InitProjectile(const FProjectileProperties& ProjectileInfo)
{
	SetLifeSpan(ProjectileInfo.ProjectileLifeSpan);

	ProjectileMovement->InitialSpeed = ProjectileInfo.ProjectileSpeed;
	ProjectileMovement->MaxSpeed = ProjectileInfo.ProjectileSpeed;
	ProjectileMovement->bShouldBounce = ProjectileInfo.bShouldBounce;
	ProjectileMovement->Bounciness = ProjectileInfo.Bounciness;
	ProjectileMovement->ProjectileGravityScale = ProjectileInfo.GravityScale;
}

