// Created by Bruce Crum.


#include "Phoenix/GameFramework/Explosions/ExplosionComponent.h"
#include "Phoenix/GameFramework/PhoenixGameplayStatics.h"

// Sets default values for this component's properties
UExplosionComponent::UExplosionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	DefaultExplosionData = nullptr;
}

void UExplosionComponent::Explode(APawn* Instigator /*= nullptr*/, UExplosionData* ExplosionOverride /*= nullptr */)
{
	const auto ChosenData = ExplosionOverride != nullptr ? ExplosionOverride : DefaultExplosionData;

	FExplosionInfo Info;
	Info.ExplodingActor = GetOwner();
	Info.Location = GetComponentLocation();
	Info.ExplosionData = ChosenData;
	Info.Instigator = Instigator;

	UPhoenixGameplayStatics::Explode(this, Info);
}
