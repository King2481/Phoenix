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

	if (DefaultHealthEntrys.Num() > 0)
	{
		HealthEntrys.Append(DefaultHealthEntrys);
	}

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
		HealthEntrys.Sort();
	}
}

void UHealthComponent::RemoveHealthTypeEntry(const FHealthTypeEntry& HealthTypeToRemove)
{
	if (HealthEntrys.Contains(HealthTypeToRemove))
	{
		HealthEntrys.Remove(HealthTypeToRemove);
		HealthEntrys.Sort();
	}
}

float UHealthComponent::GetHealthRemainingAsRatio() const
{
	int32 AddedAmount = 0, AddedMaxAmount = 0;

	for (const FHealthTypeEntry& Entry : HealthEntrys)
	{
		AddedAmount += Entry.Amount;
		AddedMaxAmount += Entry.MaxAmount;
	}

	return float(AddedAmount) / float(AddedMaxAmount);
}

void UHealthComponent::OnHealthUpdatedEvent(const FModifyHealthInfo& ModifyHealthInfo)
{
	FHealthChangeResult Result;

	for (const FDamageInfo& Damage : ModifyHealthInfo.DamageSources)
	{
		Result.DamageSources.Add(Damage);

		for (int32 Index = HealthEntrys.Num() - 1; Index >= 0; --Index)
		{
			FHealthTypeEntry& Entry = HealthEntrys[Index];

			Entry.Amount -= Damage.ChangeAmount;

			if (Entry.Amount <= 0.0f)
			{
				if (Entry.HealthType->bIsCritical)
				{
					OnDeathDelegate.Broadcast(FOnDeathInfo(GetOwner(), ModifyHealthInfo.CausedBy));
					goto endloop; // I know it is generally frowned upon to use goto, but from my understanding, using it to break out of nested for loops is completely fine.
				}
				else
				{
					HealthEntrys.RemoveSingleSwap(Entry);
				}
			}
		}

		if (HealthEntrys.Num() >= 1)
		{
			HealthEntrys.Sort();
		}
	}

endloop:

	Result.CurrentHealthPools.Append(GetHealthTypeEntries());
	Result.HealthRemainingAsRatio = GetHealthRemainingAsRatio();

	OnHealthChangedDelegate.Broadcast(Result);
}