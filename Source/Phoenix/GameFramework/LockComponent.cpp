// Created by Bruce Crum.


#include "Phoenix/GameFramework/LockComponent.h"
#include "Phoenix/GameFramework/NameComponent.h"
#include "Phoenix/Items/InventoryComponent.h"

// Sets default values for this component's properties
ULockComponent::ULockComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetComponentTickEnabled(false);

	LockState = ELockState::Unlocked;
	DifficultyClass = FDifficultyClassInfo();
	RequiredItem = nullptr;
}

void ULockComponent::BeginPlay()
{
	Super::BeginPlay();

	LockState = DifficultyClass >= 1 ? ELockState::Locked : ELockState::Unlocked;
	
	if (!IsUnlocked())
	{
		UpdateOwnerName();
	}
}

void ULockComponent::SetLockState(const ELockState NewLockState)
{
	LockState = NewLockState;
	UpdateOwnerName();

	OnLockStateChangedDelegate.Broadcast(NewLockState);
}

bool ULockComponent::CanUnlock(const AActor* UnlockingActor) const
{
	if (IsBroken() || IsUnlocked())
	{
		return true;
	}

	if (IsJammed())
	{
		return false;
	}

	if (UnlockingActor)
	{
		if (const auto Inventory = UnlockingActor->FindComponentByClass<UInventoryComponent>())
		{
			return Inventory->HasItem(RequiredItem) >= 1;
		}
	}

	return false;
}

void ULockComponent::UpdateOwnerName()
{
	if (const auto NameComp = GetOwner()->GetComponentByClass<UNameComponent>())
	{
		if (IsUnlocked())
		{
			NameComp->RemoveFromAppendix(this);
		}
		else
		{
			auto LockStateToText = [](ELockState State) -> FText
			{
				switch (State)
				{
					case ELockState::Locked:
						return NSLOCTEXT("LockComponentNamespace", "LockedText", "Locked");
					case ELockState::Jammed:
						return NSLOCTEXT("LockComponentNamespace", "JammedText", "Jammed");
					case ELockState::Broken:
						return NSLOCTEXT("LockComponentNamespace", "BrokenText", "Broken");
					default:
						return FText::FromString(TEXT("ERR"));
				}
			};

			NameComp->AddToTextAppendix(FTextAppendix(this, LockStateToText(LockState)));
		}
	}
}