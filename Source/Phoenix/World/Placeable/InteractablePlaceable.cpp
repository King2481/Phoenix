// Created by Bruce Crum.


#include "Phoenix/World/Placeable/InteractablePlaceable.h"
#include "Phoenix/GameFramework/Targeting/TargetingComponent.h"
#include "Phoenix/Abilities/PhoenixAbilitySystemComponent.h"

AInteractablePlaceable::AInteractablePlaceable()
{
	TargetingComponent = CreateDefaultSubobject<UTargetingComponent>(TEXT("TargetingComponent"));
	AbilitySystem = CreateDefaultSubobject<UPhoenixAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	NameComponent = CreateDefaultSubobject<UNameComponent>(TEXT("NameComponent"));
}