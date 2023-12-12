// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Phoenix/Weapons/ItemDataWeapon.h"
#include "ItemDataFirearm.generated.h"

class UAmmoType;
class UFireModeType;

USTRUCT(BlueprintType)
struct FFireModeInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TObjectPtr<UFireModeType> FireMode;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (ClampMin = "1", UIMin = "1"))
	int32 BulletsToFire;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bRollToHit;

	FFireModeInfo()
	{
		FireMode = nullptr;
		BulletsToFire = 1;
		bRollToHit = true;
	}
};

/**
 * 
 */
UCLASS()
class PHOENIX_API UItemDataFirearm : public UItemDataWeapon
{
	GENERATED_BODY()
	
public:

	UItemDataFirearm();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Firearm")
	TArray<TObjectPtr<UAmmoType>> AccetableAmmoTypes;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data Firearm")
	TArray<FFireModeInfo> AvailableFireModes;

};
