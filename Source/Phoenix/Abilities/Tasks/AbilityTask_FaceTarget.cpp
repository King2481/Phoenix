// Created by Bruce Crum.


#include "Phoenix/Abilities/Tasks/AbilityTask_FaceTarget.h"

UAbilityTask_FaceTarget::UAbilityTask_FaceTarget()
{
	bTickingTask = true;

	TargetActor = nullptr;
	RotationSpeed = 10.0f;
}

UAbilityTask_FaceTarget* UAbilityTask_FaceTarget::FaceTarget(UGameplayAbility* OwningAbility, AActor* InTargetActor, float InRotationSpeed /*= 10.0f*/)
{
	const auto MyObj = NewAbilityTask<UAbilityTask_FaceTarget>(OwningAbility, NAME_None);
	if (MyObj)
	{
		MyObj->TargetActor = InTargetActor;
		MyObj->RotationSpeed = InRotationSpeed;
	}

	return MyObj;
}

void UAbilityTask_FaceTarget::Activate()
{
	Super::Activate();

}

void UAbilityTask_FaceTarget::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);

}

void UAbilityTask_FaceTarget::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	const FVector DirectionToTarget = (TargetActor->GetActorLocation() - GetAvatarActor()->GetActorLocation()).GetSafeNormal();
	const FVector HorizontalDirection = FVector(DirectionToTarget.X, DirectionToTarget.Y, 0.0f);
	const float TargetYaw = FMath::Atan2(HorizontalDirection.Y, HorizontalDirection.X) * 180.0f / PI;
	const float CurrentYaw = GetAvatarActor()->GetActorRotation().Yaw;

	const float InterpedYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, RotationSpeed);

	FRotator NewRotation = GetAvatarActor()->GetActorRotation();
	NewRotation.Yaw = InterpedYaw;
	GetAvatarActor()->SetActorRotation(NewRotation);

	if (FMath::IsNearlyEqual(InterpedYaw, TargetYaw, 1.0f))
	{
		OnRequestFinished.Broadcast();
		EndTask();
	}
}
