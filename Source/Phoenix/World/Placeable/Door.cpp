// Created by Bruce Crum.


#include "Phoenix/World/Placeable/Door.h"
#include "Phoenix/GameFramework/Health/HealthComponent.h"
#include "Phoenix/GameFramework/NameComponent.h"

ADoor::ADoor()
{
	DoorState = EDoorState::Closed;

	LockComponent = CreateDefaultSubobject<ULockComponent>(TEXT("LockComponent"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void ADoor::TransitionToState(const EDoorState NewState)
{
	DoorState = NewState;

	BlueprintTransitionToState(DoorState);
}

FTargetableInfo ADoor::GetTargetInfo_Implementation() const
{
	return FTargetableInfo(HealthComponent, AbilitySystem, TargetingComponent, NameComponent->GetDisplayName());
}