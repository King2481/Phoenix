// Created by Bruce Crum.


#include "Phoenix/GameFramework/Health/HealthComponent.h"
#include "Phoenix/Abilities/PhoenixAbilitySystemComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetComponentTickEnabled(false);

	// ...
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (const auto ABS = GetOwner()->GetComponentByClass<UPhoenixAbilitySystemComponent>())
	{
		ABS->ChangeHealthInfoDelegate.AddDynamic(this, &ThisClass::OnHealthUpdatedEvent);
	}
}

void UHealthComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (const auto ABS = GetOwner()->GetComponentByClass<UPhoenixAbilitySystemComponent>())
	{
		ABS->ChangeHealthInfoDelegate.RemoveDynamic(this, &ThisClass::OnHealthUpdatedEvent);
	}

	Super::EndPlay(EndPlayReason);
}

void UHealthComponent::AddHealthTypeEntry(const FHealthTypeEntry& HealthTypeToAdd)
{
	if (!HealthEntrys.Contains(HealthTypeToAdd))
	{
		HealthEntrys.AddUnique(HealthTypeToAdd);
		HealthEntrys.Sort(UHealthComponent::SortHealthTypePriority);
	}
}

void UHealthComponent::RemoveHealthTypeEntry(const FHealthTypeEntry& HealthTypeToRemove)
{
	if (HealthEntrys.Contains(HealthTypeToRemove))
	{
		HealthEntrys.Remove(HealthTypeToRemove);
		HealthEntrys.Sort(UHealthComponent::SortHealthTypePriority);
	}
}

void UHealthComponent::OnHealthUpdatedEvent(const FModifyHealthInfo& ModifyHealthInfo)
{
	for (FHealthTypeEntry& Entry : HealthEntrys)
	{
		for (FDamageInfo Damage : ModifyHealthInfo.DamageSources)
		{
			HealthEntrys[0].Amount -= Damage.ChangeAmount;

			if (HealthEntrys[0].Amount <= 0.0f)
			{
				if (HealthEntrys[0].HealthType->bIsCritical)
				{
					OnDeathDelegate.Broadcast(FOnDeathInfo(GetOwner(), ModifyHealthInfo.CausedBy));
					goto endloop; // I know it is generally frowned upon to use goto, but from my understanding, using it to break out of nested for loops is completely fine.
				}
				else
				{
					HealthEntrys.Remove(Entry);
					HealthEntrys.Sort(UHealthComponent::SortHealthTypePriority);
				}
			}
		}
	}

endloop:

	OnHealthChangedDelegate.Broadcast(FHealthChangeResult());
}