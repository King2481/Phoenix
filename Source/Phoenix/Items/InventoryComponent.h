// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryTypes.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdatedDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHOENIX_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// Sets default values for this component's properties
	UInventoryComponent();

	// Checks to see if we actually have the specifed item and returns the amount of that item we have.
	UFUNCTION(BlueprintPure, Category = "Iventory Component")
	int32 HasItem(const UItemDataBase* ItemToFind);

	// Adds an item to our inventory
	UFUNCTION(BlueprintCallable, Category = "Iventory Component")
	void AddItem(UItemDataBase* ItemToAdd, const int32 Amount = 1);

	// Removes an item from our inventory.
	UFUNCTION(BlueprintCallable, Category = "Iventory Component")
	bool RemoveItem(UItemDataBase* ItemToRemove, const int32 Amount = 1);

	// Returns the inventory items this component has.
	UFUNCTION(BlueprintPure, Category = "Iventory Component")
	TArray<FInventoryItem> GetInventoryItems() const { return InventoryItems; }

	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdatedDelegate OnInventoryUpdatedDelegate;

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called when the components ends play.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// A list of all our inventory items.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Iventory Component")
	TArray<FInventoryItem> InventoryItems;
		
};
