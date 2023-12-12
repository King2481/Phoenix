// Created by Bruce Crum.


#include "Phoenix/Characters/EquipmentManager.h"
#include "Phoenix/Characters/Equipable.h"
#include "Phoenix/Characters/EquipmentSlotLayout.h"
#include "Phoenix/Items/ItemDataEquipable.h"
#include "Phoenix/Items/InventoryComponent.h"
#include "Phoenix/Abilities/PhoenixAbilitySystemComponent.h"

// Sets default values for this component's properties
UEquipmentManager::UEquipmentManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetComponentTickEnabled(false);

	Layout = nullptr;
}

void UEquipmentManager::BeginPlay()
{
	Super::BeginPlay();

	if (Layout)
	{
		for (UItemEquipableSlot* Slot : Layout->AcceptableSlots)
		{
			EquippedItems.Add(Slot);
		}
	}
	else
	{
		// TODO: Log
	}
}

void UEquipmentManager::AddItemToSlot(UItemDataEquipable* InEquipable, UItemEquipableSlot* InSlot)
{
	for (FSlotInfo& SlotInfo : EquippedItems)
	{
		if (SlotInfo.Slot == InSlot)
		{
			// TODO: Multihanded items.
			TArray<UItemEquipableSlot*> Slots;
	
			if (SlotInfo.OccupiedBy != nullptr && SlotInfo.OccupiedBy->bRequiresMultipleSlotsToEquip)
			{
				Slots.Append(SlotInfo.OccupiedBy->OpenSlotsNeededToEquip);
			}
			else
			{
				Slots.Add(InSlot);
			}

			if (SlotInfo.OccupiedBy != nullptr)
			{
				RemoveItemFromSlot(InSlot);
			}

			SlotInfo = FSlotInfo(InSlot, InEquipable);

			InEquipable->OnEquip(GetOwner());

			if (const auto ABS = GetOwner()->GetComponentByClass<UPhoenixAbilitySystemComponent>())
			{
				for (TSubclassOf<UPhoenixGameplayAbility> Ability : InEquipable->GrantedAbilitiesOnEquip)
				{
					ABS->GivePhoenixAbility(Ability);
				}
			}

			if (const auto Inventory = GetOwner()->GetComponentByClass<UInventoryComponent>())
			{
				Inventory->RemoveItem(InEquipable);
			}
		}
	}
}

void UEquipmentManager::RemoveItemFromSlot(UItemEquipableSlot* InSlot)
{
	for (FSlotInfo& SlotInfo : EquippedItems)
	{
		if (SlotInfo.Slot == InSlot)
		{
			SlotInfo.OccupiedBy->OnUnequip(GetOwner());

			if (const auto ABS = GetOwner()->GetComponentByClass<UPhoenixAbilitySystemComponent>())
			{
				for (TSubclassOf<UPhoenixGameplayAbility> Ability : SlotInfo.OccupiedBy->GrantedAbilitiesOnEquip)
				{
					ABS->ClearPhoenixAbility(Ability);
				}
			}

			if (const auto Inventory = GetOwner()->GetComponentByClass<UInventoryComponent>())
			{
				Inventory->AddItem(SlotInfo.OccupiedBy);
			}

			SlotInfo = FSlotInfo();
		}
	}
}

UItemDataEquipable* UEquipmentManager::GetItemInSlot(const UItemEquipableSlot* InSlot) const
{
	for (const FSlotInfo& SlotInfo : EquippedItems)
	{
		if (SlotInfo.Slot == InSlot)
		{
			return SlotInfo.OccupiedBy;
		}
	}

	// TODO: Log
	return nullptr;
}

