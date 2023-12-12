// Created by Bruce Crum.


#include "Phoenix/GameFramework/Reputation/ReputationComponent.h"

// Sets default values for this component's properties
UReputationComponent::UReputationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetComponentTickEnabled(false);

	CurrentFaction = nullptr;
}

void UReputationComponent::AddToReputation(UReputationInfo* InReputation)
{

}