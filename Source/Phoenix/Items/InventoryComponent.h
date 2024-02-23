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
	UFUNCTION(BlueprintPure, Category = "Inventory Component")
	int32 HasItem(const UItemDataBase* ItemToFind);

	// Adds an item to our inventory
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	void AddItem(UItemDataBase* ItemToAdd, const int32 Amount = 1);

	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	void AddItemFromItemStruct(const FInventoryItem& InInventoryItem);

	// Removes an item from our inventory.
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	bool TransferItemBetweenInventories(const FInventoryItem& InInventoryItem, UInventoryComponent* From);

	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	void AttemptToTransferAllItemBetweenInventories(UInventoryComponent* From);

	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	bool RemoveItem(UItemDataBase* ItemToRemove, const int32 Amount = 1);

	// Returns the inventory items this component has.
	UFUNCTION(BlueprintPure, Category = "Inventory Component")
	TArray<FInventoryItem> GetInventoryItems() const { return InventoryItems; }

	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdatedDelegate OnInventoryUpdatedDelegate;

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called when the components ends play.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// A list of all our inventory items.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Inventory Component")
	TArray<FInventoryItem> InventoryItems;
		
};
