// Created by Bruce Crum.


#include "Phoenix/World/Placeable/StorageContainer.h"
#include "Phoenix/Items/InventoryComponent.h"
#include "Phoenix/GameFramework/NameComponent.h"
#include "Phoenix/GameFramework/LockComponent.h"

// Sets default values
AStorageContainer::AStorageContainer()
{
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	LockComponent = CreateDefaultSubobject<ULockComponent>(TEXT("LockComponent"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

FTargetableInfo AStorageContainer::GetTargetInfo_Implementation() const
{
	return FTargetableInfo(nullptr, AbilitySystem, TargetingComponent, NameComponent->GetDisplayName());
}
