// Created by Bruce Crum.


#include "Phoenix/Weapons/Ammo/AmmoComponent.h"

// Sets default values for this component's properties
UAmmoComponent::UAmmoComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	LoadedAmmo = nullptr;
	AmmoLeft = 0;
}

void UAmmoComponent::LoadAmmo(UItemDataAmmo* InAmmo, int32 InAmount)
{
	LoadedAmmo = InAmmo;
	AmmoLeft = InAmount;
}

void UAmmoComponent::OnRoundFired()
{
	AmmoLeft--;
}

int32 UAmmoComponent::GetActualAvailableAmmoFromRequestedAmmo(const int32 RequestedAmmo) const
{
	return FMath::Min<int32>(AmmoLeft, RequestedAmmo);
}