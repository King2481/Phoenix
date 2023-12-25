// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_FaceTarget.generated.h"

/**
 * 
 */
UCLASS()
class PHOENIX_API UAbilityTask_FaceTarget : public UAbilityTask
{
	GENERATED_BODY()

public:

	UAbilityTask_FaceTarget();

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_FaceTarget* FaceTarget(UGameplayAbility* OwningAbility, AActor* InTargetActor, float InRotationSpeed = 10.0f);
	
protected:

	UPROPERTY(BlueprintAssignable)
	FGenericGameplayTaskDelegate OnRequestFinished;

	virtual void Activate() override;
	virtual void OnDestroy(bool bOwnerFinished) override;
	virtual void TickTask(float DeltaTime) override;

	TObjectPtr<AActor> TargetActor;
	float RotationSpeed;

};
