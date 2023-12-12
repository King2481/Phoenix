// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AmmoComponent.generated.h"

class UItemDataAmmo;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHOENIX_API UAmmoComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAmmoComponent();

	UFUNCTION(BlueprintPure, Category = "Ammo Component")
	bool HasAmmo() const { return AmmoLeft > 0; }

	UFUNCTION(BlueprintPure, Category = "Ammo Component")
	UItemDataAmmo* GetLoadedAmmo() const { return LoadedAmmo; }

	UFUNCTION(BlueprintCallable, Category = "Ammo Component")
	void LoadAmmo(UItemDataAmmo* InAmmo, int32 InAmount);

	UFUNCTION(BlueprintCallable, Category = "Ammo Component")
	void OnRoundFired();

	UFUNCTION(BlueprintPure, Category = "Ammo Component")
	int32 GetActualAvailableAmmoFromRequestedAmmo(const int32 RequestedAmmo) const;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Ammo Component")
	TObjectPtr<UItemDataAmmo> LoadedAmmo;

	UPROPERTY(BlueprintReadOnly, Category = "Ammo Component")
	int32 AmmoLeft;

};
