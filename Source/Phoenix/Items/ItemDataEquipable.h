// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Phoenix/Items/ItemDataBase.h"
#include "ItemDataEquipable.generated.h"

class UPhoenixGameplayAbility;
class UGameplayEffect;
class UItemEquipableSlot;
class UItemRequirement;

/**
 * 
 */
UCLASS(BlueprintType)
class PHOENIX_API UItemDataEquipable : public UItemDataBase
{
	GENERATED_BODY()

public:

	UItemDataEquipable();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Equipable")
	TArray<TSubclassOf<UPhoenixGameplayAbility>> GrantedAbilitiesOnEquip;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Equipable")
	TArray<TSubclassOf<UGameplayEffect>> GrantedEffectsOnEquip;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Equipable")
	TArray<TObjectPtr<UItemEquipableSlot>> AccaptableSlots;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Equipable")
	bool bRequiresMultipleSlotsToEquip;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Equipable", meta = (EditCondition = "bRequiresMultipleSlotsToEquip", EditConditionHides))
	TArray<TObjectPtr<UItemEquipableSlot>> OpenSlotsNeededToEquip;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced, Category = "Item Data Equipable")
	TArray<TObjectPtr<UItemRequirement>> EquipRequirements;

	virtual void OnEquip(AActor* EquippingActor) { };

	virtual void OnUnequip(AActor* UnequippingActor) { };

};
