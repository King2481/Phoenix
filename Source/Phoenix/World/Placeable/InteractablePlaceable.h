// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Phoenix/World/Placeable/PlaceableBase.h"
#include "Phoenix/GameFramework/Targeting/Targetable.h"
#include "InteractablePlaceable.generated.h"

class UTargetingComponent;
class UPhoenixAbilitySystemComponent;
class UNameComponent;

/**
 * 
 */
UCLASS()
class PHOENIX_API AInteractablePlaceable : public APlaceableBase, public ITargetable
{
	GENERATED_BODY()

public:

	AInteractablePlaceable();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactable Placeable")
	TObjectPtr<UTargetingComponent> TargetingComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactable Placeable")
	TObjectPtr<UPhoenixAbilitySystemComponent> AbilitySystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactable Placeable")
	TObjectPtr<UNameComponent> NameComponent;
};
