// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentManager.generated.h"

class UEquipmentSlotLayout;
class UItemEquipableSlot;
class UItemDataEquipable;

USTRUCT(BlueprintType)
struct FSlotInfo 
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UItemEquipableSlot> Slot;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UItemDataEquipable> OccupiedBy;

	FSlotInfo()
	{
		Slot = nullptr;
		OccupiedBy = nullptr;
	}

	FSlotInfo(UItemEquipableSlot* InSlot)
	{
		Slot = InSlot;
		OccupiedBy = nullptr;
	}

	FSlotInfo(UItemEquipableSlot* InSlot, UItemDataEquipable* InOccupiedBy)
	{
		Slot = InSlot;
		OccupiedBy = InOccupiedBy;
	}
	
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHOENIX_API UEquipmentManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentManager();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Equipment Manager")
	void AddItemToSlot(UItemDataEquipable* InEquipable, UItemEquipableSlot* InSlot);

	UFUNCTION(BlueprintCallable, Category = "Equipment Manager")
	void RemoveItemFromSlot(UItemEquipableSlot* InSlot);

	UFUNCTION(BlueprintPure, Category = "Equipment Manager")
	UItemDataEquipable* GetItemInSlot(const UItemEquipableSlot* InSlot) const;

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Equipment Manager")
	TObjectPtr<UEquipmentSlotLayout> Layout;

	UPROPERTY(BlueprintReadOnly, Category = "Equipment Manager")
	TArray<FSlotInfo> EquippedItems;
};
