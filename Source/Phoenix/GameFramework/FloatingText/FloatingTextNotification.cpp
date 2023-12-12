// Created by Bruce Crum.


#include "Phoenix/GameFramework/FloatingText/FloatingTextNotification.h"
#include "Phoenix/GameFramework/Health/HealthComponent.h"

// Sets default values for this component's properties
UFloatingTextNotification::UFloatingTextNotification()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetComponentTickEnabled(false);

}


// Called when the game starts
void UFloatingTextNotification::BeginPlay()
{
	Super::BeginPlay();

	if (const auto HealthComponent = GetOwner()->GetComponentByClass<UHealthComponent>())
	{
		HealthComponent->OnHealthChangedDelegate.AddDynamic(this, &ThisClass::OnOwnersHealthChanged);
	}
}

void UFloatingTextNotification::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (const auto HealthComponent = GetOwner()->GetComponentByClass<UHealthComponent>())
	{
		HealthComponent->OnHealthChangedDelegate.RemoveDynamic(this, &ThisClass::OnOwnersHealthChanged);
	}

	Super::EndPlay(EndPlayReason);
}

void UFloatingTextNotification::OnOwnersHealthChanged(const FHealthChangeResult& NewInfo)
{

}


