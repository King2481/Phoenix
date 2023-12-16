// Created by Bruce Crum.


#include "Phoenix/Items/InventoryComponent.h"
#include "Phoenix/Items/ItemDataBase.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetComponentTickEnabled(false);

	// ...
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

void UInventoryComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// TODO: Destroy inventory items when play is ended.

	Super::EndPlay(EndPlayReason);
}

int32 UInventoryComponent::HasItem(const UItemDataBase* ItemToFind)
{
	int32 Amount = 0;

	for (FInventoryItem& InventoryItem : InventoryItems)
	{
		if (InventoryItem.Item == ItemToFind)
		{
			Amount += InventoryItem.Count;
		}
	}

	return Amount;
}

void UInventoryComponent::AddItemFromItemStruct(const FInventoryItem& InInventoryItem)
{
	AddItem(InInventoryItem.Item, InInventoryItem.Count);
}

void UInventoryComponent::AddItem(UItemDataBase* ItemToAdd, const int32 Amount /*= 1 */ )
{
	int32 LocalAmount = Amount;

	if (ItemToAdd->bStackable)
	{
		for (FInventoryItem& InventoryItem : InventoryItems)
		{
			if (InventoryItem.Item == ItemToAdd)
			{
				const int32 SpaceLeftInStack = ItemToAdd->MaximumAmount - InventoryItem.Count;
				if (LocalAmount <= SpaceLeftInStack)
				{
					// There's enough space in the stack for the entire amount.
					InventoryItem.Count += LocalAmount;
					return;
				}
				else
				{
					// Fill the stack to its maximum capacity and add the remaining to a new item.
					InventoryItem.Count = ItemToAdd->MaximumAmount;
					LocalAmount -= SpaceLeftInStack;
				}
			}
		}
	}

	// Couldn't find it, not a stackable item, or stackable item has reached its limit and we need a new one.
	while (LocalAmount > 0)
	{
		const int32 StackSize = FMath::Min<int32>(LocalAmount, ItemToAdd->MaximumAmount);
		FInventoryItem NewItem(ItemToAdd, StackSize);
		InventoryItems.Add(NewItem);
		LocalAmount -= StackSize;
	}

	OnInventoryUpdatedDelegate.Broadcast();
}

bool UInventoryComponent::RemoveItem(UItemDataBase* ItemToRemove, const int32 Amount /*= 1 */)
{
	int32 RemainingAmountToRemove = Amount;

	for (int i = 0; i <= InventoryItems.Num() - 1; i++)
	{
		if (FInventoryItem InventoryItem = InventoryItems[i])
		{
			if (InventoryItem.Item == ItemToRemove)
			{
				if (RemainingAmountToRemove >= InventoryItem.Count)
				{
					// Remove the entire stack and update the remaining amount.
					RemainingAmountToRemove -= InventoryItem.Count;
					InventoryItems.RemoveAt(i);
				}
				else
				{
					// Remove the specified amount and update the stack size.
					InventoryItem.Count -= RemainingAmountToRemove;
					RemainingAmountToRemove = 0;
					break;
				}
			}
		}
	}

	OnInventoryUpdatedDelegate.Broadcast();

	// Did we actually remove anything?
	return RemainingAmountToRemove != Amount;
}

bool UInventoryComponent::TransferItemBetweenInventories(const FInventoryItem& InInventoryItem, UInventoryComponent* From)
{
	if (From->RemoveItem(InInventoryItem.Item, InInventoryItem.Count))
	{
		AddItemFromItemStruct(InInventoryItem);
		return true;
	}

	return false;
}

void UInventoryComponent::AttemptToTransferAllItemBetweenInventories(UInventoryComponent* From)
{
	for (FInventoryItem& Item : From->GetInventoryItems())
	{
		TransferItemBetweenInventories(Item, From);
	}

	// TODO: Log how many items were successfully added.
}

