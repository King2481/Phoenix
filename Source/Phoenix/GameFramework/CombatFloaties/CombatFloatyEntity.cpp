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
}