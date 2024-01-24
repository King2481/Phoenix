// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Phoenix/Items/ItemDataHandEquipable.h"
#include "Phoenix/GameFramework/PhoenixTypes.h"
#include "ItemDataWeapon.generated.h"

class UPhoenixGameplayAbility;

/**
 * 
 */
UCLASS()
class PHOENIX_API UItemDataWeapon : public UItemDataHandEquipable
{
	GENERATED_BODY()
	
public:

	UItemDataWeapon();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Weapon")
	TArray<FDamageCalculationInfo> DamageCalculationInfo;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Weapon")
	TSubclassOf<UPhoenixGameplayAbility> MainHandAttackAbility;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Weapon", meta = (ClampMin = "1", ClampMax = "20", UIMin = "1", UIMax = "20"))
	int32 CritDie;

	virtual void OnEquip(AActor* EquippingActor) override;
	virtual void OnUnequip(AActor* UnequippingActor) override;

};
