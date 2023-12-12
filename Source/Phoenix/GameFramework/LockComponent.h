// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhoenixTypes.h"
#include "LockComponent.generated.h"

class UItemDataBase;

UENUM(BlueprintType)
enum class ELockState : uint8
{
	Unlocked   UMETA(DisplayName = "Unlocked"),
	Locked     UMETA(DisplayName = "Locked"),
	Broken     UMETA(DisplayName = "Broken"),
	Jammed     UMETA(DisplayName = "Jammed"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLockStateChangedDelegate, ELockState, NewState);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHOENIX_API ULockComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULockComponent();

	// Called when the owning acotr begins play.
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Lock Component")
	void SetLockState(const ELockState NewLockState);

	UFUNCTION(BlueprintPure, Category = "Lock Component")
	bool IsUnlocked() const { return LockState == ELockState::Unlocked; }

	UFUNCTION(BlueprintPure, Category = "Lock Component")
	bool IsLocked() const { return LockState == ELockState::Locked; }

	UFUNCTION(BlueprintPure, Category = "Lock Component")
	bool IsBroken() const { return LockState == ELockState::Broken; }

	UFUNCTION(BlueprintPure, Category = "Lock Component")
	bool IsJammed() const { return LockState == ELockState::Jammed; }

	// Checks to see if we can unlock the component.
	UFUNCTION(BlueprintPure, Category = "Lock Component")
	bool CanUnlock(const AActor* UnlockingActor) const;

	UPROPERTY(BlueprintAssignable)
	FOnLockStateChangedDelegate OnLockStateChangedDelegate;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Lock Component")
	ELockState LockState;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Lock Component")
	FDifficultyClassInfo DifficultyClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Lock Component")
	TObjectPtr<UItemDataBase> RequiredItem;

private:

	void UpdateOwnerName();

};
