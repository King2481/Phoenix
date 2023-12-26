// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Phoenix/GameFramework/PhoenixTypes.h" // FProjectileProperties
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;

UCLASS()
class PHOENIX_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AProjectileBase();

	virtual void InitProjectile(const FProjectileProperties& ProjectileInfo);

protected:

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Base")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;


};
