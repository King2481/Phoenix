// Created by Bruce Crum.


#include "Phoenix/Abilities/AbilityTask_FaceTarget.h"

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
	const FRotator CurrentRotation = GetAvatarActor()->GetActorRotation();
	const FRotator DesiredRotation = CurrentRotation.Quaternion().RotateVector(DirectionToTarget).Rotation();
	const FRotator InterpedRotation = FMath::RInterpTo(CurrentRotation, DesiredRotation, DeltaTime, RotationSpeed);

	GetAvatarActor()->SetActorRotation(InterpedRotation);

	if (FVector::DotProduct(GetAvatarActor()->GetActorForwardVector(), DirectionToTarget) >= 0.9999f)
	{
		OnRequestFinished.Broadcast();
		EndTask();
	}
}
