// Created by Bruce Crum.


#include "Phoenix/Abilities/PhoenixAbilitySystemComponent.h"
#include "Phoenix/Abilities/PhoenixGameplayAbility.h"

UPhoenixAbilitySystemComponent::UPhoenixAbilitySystemComponent()
{
	CurrentTargetData = FTargetData();
}

void UPhoenixAbilitySystemComponent::GivePhoenixAbility(TSubclassOf<UPhoenixGameplayAbility> Ability)
{
	if (Ability)
	{
		GiveAbility(FGameplayAbilitySpec(Ability, 0, -1, this));
	}
}

void UPhoenixAbilitySystemComponent::ClearPhoenixAbility(TSubclassOf<UPhoenixGameplayAbility> Ability)
{
	if (Ability)
	{
		for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
		{
			if (Spec.Ability->GetClass() == Ability)
			{
				ClearAbility(FGameplayAbilitySpecHandle(Spec.Handle));
				return;
			}
		}
	}
}

void UPhoenixAbilitySystemComponent::SetTargetDataAndTryAbility(const FTargetData& InTargetData, TSubclassOf<UPhoenixGameplayAbility> Ability)
{
	CurrentTargetData = InTargetData;
	TryActivateAbilityByClass(Ability);
}

void UPhoenixAbilitySystemComponent::ModifyHealth(const FModifyHealthInfo& ModifyHealthInfo)
{
	ChangeHealthInfoDelegate.Broadcast(ModifyHealthInfo);
}
