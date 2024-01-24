// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Phoenix/Items/ItemDataBase.h"
#include "ItemDataAmmo.generated.h"

class UAmmoType;
class UBulletFiringData;

/**
 * 
 */
UCLASS()
class PHOENIX_API UItemDataAmmo : public UItemDataBase
{
	GENERATED_BODY()

public:
	
	UItemDataAmmo();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Ammo")
	TObjectPtr<UAmmoType> AmmoType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Ammo")
	TObjectPtr<UBulletFiringData> BulletFiringData;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Ammo")
	TObjectPtr<UStaticMesh> AmmoCasing;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Ammo", meta = (ClampMin = "0", ClampMax = "20", UIMin = "0", UIMax = "20"))
	int32 CritDieBonus;
};
