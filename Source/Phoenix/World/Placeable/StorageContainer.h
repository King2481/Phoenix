// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Phoenix/World/Placeable/InteractablePlaceable.h"
#include "StorageContainer.generated.h"

class UInventoryComponent;
class ULockComponent;

UCLASS()
class PHOENIX_API AStorageContainer : public AInteractablePlaceable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStorageContainer();

	virtual FTargetableInfo GetTargetInfo_Implementation() const override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Storage Container")
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Storage Container")
	TObjectPtr<ULockComponent> LockComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Storage Container")
	TObjectPtr<UStaticMeshComponent> Mesh;

};
