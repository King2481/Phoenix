// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Phoenix/Items/ItemDataEquipable.h"
#include "ItemDataHandEquipable.generated.h"

class AProp;

/**
 * 
 */
UCLASS()
class PHOENIX_API UItemDataHandEquipable : public UItemDataEquipable
{
	GENERATED_BODY()

public:

	UItemDataHandEquipable();

	// When we equip this item, what is the associated prop?
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Hand Equipable")
	TSoftClassPtr<AProp> AssociatedProp;

	virtual void OnEquip(AActor* EquippingActor) override;
	virtual void OnUnequip(AActor* UnequippingActor) override;

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Hand Equipable")
	FName EquippedSocketName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Hand Equipable")
	FName UnequippedSocketName;

	UPROPERTY(BlueprintReadOnly, Category = "Item Data Hand Equipable")
	TObjectPtr<AProp> SpawnedProp;
};
