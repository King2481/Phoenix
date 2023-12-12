// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Prop.generated.h"

UENUM(BlueprintType)
enum class EEquipableState : uint8
{
	Unequipped 	  UMETA(DisplayName = "Unequipped"),
	Unequipping   UMETA(DisplayName = "Unequipping"),
	Equipping	  UMETA(DisplayName = "Equipping"),
	Equipped      UMETA(DisplayName = "Equipped")
};

UCLASS()
class PHOENIX_API AProp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProp();

	// Set the equipable state.
	UFUNCTION(BlueprintCallable, Category = "Prop")
	void SetEquipableState(EEquipableState NewState);

protected:

	// Prop Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Prop")
	TObjectPtr<USkeletalMeshComponent> Mesh;

	// The current equipable state of the item.
	UPROPERTY(BlueprintReadOnly, Category = "Prop")
	EEquipableState EquipableState;

};
