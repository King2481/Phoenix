// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Phoenix/World/Placeable/InteractablePlaceable.h"
#include "Door.generated.h"

class ULockComponent;
class UHealthComponent;

UENUM(BlueprintType)
enum class EDoorState : uint8
{
	Closed     UMETA(DisplayName = "Closed"),
	Closing    UMETA(DisplayName = "Closing"),
	Opening    UMETA(DisplayName = "Opening"),
	Open       UMETA(DisplayName = "Open")
};

/**
 * 
 */
UCLASS()
class PHOENIX_API ADoor : public AInteractablePlaceable
{
	GENERATED_BODY()

public:

	ADoor();

	virtual FTargetableInfo GetTargetInfo_Implementation() const override;

	UFUNCTION(BlueprintPure, Category = "Door")
	EDoorState GetDoorState() { return DoorState; }

	UFUNCTION(BlueprintPure, Category = "Door")
	bool IsOpen() const { return DoorState == EDoorState::Open; }

	UFUNCTION(BlueprintPure, Category = "Door")
	bool IsOpenOrOpening() const { return IsOpen() || DoorState == EDoorState::Opening; }

	UFUNCTION(BlueprintPure, Category = "Door")
	bool IsClosed() const { return DoorState == EDoorState::Closed; }

	UFUNCTION(BlueprintPure, Category = "Door")
	bool IsClosedOrClosing() const { return IsClosed() || DoorState == EDoorState::Closing; }

	// Transitions the door to the specified state.
	UFUNCTION(BlueprintCallable, Category = "Door")
	void TransitionToState(const EDoorState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void BlueprintTransitionToState(const EDoorState NewState);

protected:

	// What is the state of this door?
	UPROPERTY(BlueprintReadOnly, Category = "Door")
	EDoorState DoorState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
	TObjectPtr<ULockComponent> LockComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
	TObjectPtr<UHealthComponent> HealthComponent;
	
};
