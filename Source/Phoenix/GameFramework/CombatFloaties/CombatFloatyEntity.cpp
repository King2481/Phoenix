// Created by Bruce Crum.


#include "Phoenix/GameFramework/CombatFloaties/CombatFloatyEntity.h"

#include "Components/TextBlock.h"

UCombatFloatyEntity::UCombatFloatyEntity(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	FlyingText = nullptr;
}

void UCombatFloatyEntity::SetCombatFloatyInfo(const FCombatFloatyCreationInfo& InInfo)
{
	FlyingText->SetText(InInfo.TextToDisplay);
	SetPositionInViewport(InInfo.RenderLocation, true);

	AddToViewport();
	BlueprintOnSpawned();
}

void UCombatFloatyEntity::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);

	OnCombatFloatyAnimationFinishedDelegate.Broadcast(this);
}