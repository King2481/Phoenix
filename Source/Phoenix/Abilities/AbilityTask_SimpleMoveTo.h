// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AITypes.h"
#include "Navigation/PathFollowingComponent.h"
#include "AbilityTask_SimpleMoveTo.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSimpleMoveTaskCompletedSignature, TEnumAsByte<EPathFollowingResult::Type>, Result, AController*, Controller);

/**
 * 
 */
UCLASS()
class PHOENIX_API UAbilityTask_SimpleMoveTo : public UAbilityTask
{
	GENERATED_BODY()

public:

	UAbilityTask_SimpleMoveTo();

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_SimpleMoveTo* SimpleMoveTo(UGameplayAbility* OwningAbility, AController* Controller, AActor* GoalActor, const FVector& TargetLocation, const float AcceptanceRadius);

	/** prepare move task for activation */
	void SetUp(AController* InController, const FAIMoveRequest& InMoveRequest);

protected:

	UPROPERTY(BlueprintAssignable)
	FSimpleMoveTaskCompletedSignature OnMoveFinished;
	
	UPROPERTY(BlueprintAssignable)
	FGenericGameplayTaskDelegate OnRequestFailed;

	virtual void Activate() override;
	virtual void OnDestroy(bool bOwnerFinished) override;

	/** finish task */
	void FinishMoveTask(EPathFollowingResult::Type InResult);

	/** start move request */
	void PerformMove();

	/** event from path following */
	void OnRequestFinished(FAIRequestID RequestID, const FPathFollowingResult& Result);

	/** parameters of move request */
	UPROPERTY()
	FAIMoveRequest MoveRequest;

	UPROPERTY(BlueprintReadOnly, Category = "AI|Tasks")
	TObjectPtr<AController> OwnerController;

	/** request ID of path following's request */
	FAIRequestID MoveRequestID;

	TEnumAsByte<EPathFollowingResult::Type> MoveResult;
	uint8 bUseContinuousTracking : 1;
	
};
