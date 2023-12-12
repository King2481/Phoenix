// Created by Bruce Crum.


#include "Phoenix/Weapons/ItemDataWeapon.h"
#include "Phoenix/Abilities/PhoenixAbilitySystemComponent.h"

UItemDataWeapon::UItemDataWeapon()
{
	MainHandAttackAbility = nullptr;
}

void UItemDataWeapon::OnEquip(AActor* EquippingActor)
{
	Super::OnEquip(EquippingActor);

	if (const auto ABS = EquippingActor->FindComponentByClass<UPhoenixAbilitySystemComponent>())
	{
		ABS->GivePhoenixAbility(MainHandAttackAbility);
	}
}

void UItemDataWeapon::OnUnequip(AActor* UnequippingActor)
{
	Super::OnUnequip(UnequippingActor);

	if (const auto ABS = UnequippingActor->FindComponentByClass<UPhoenixAbilitySystemComponent>())
	{
		ABS->ClearPhoenixAbility(MainHandAttackAbility);
	}
}