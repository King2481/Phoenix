// Created by Bruce Crum.


#include "Phoenix/GameFramework/FloatingText/FloatingTextEntity.h"

#include "Components/TextBlock.h"

UFloatingTextEntity::UFloatingTextEntity(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UFloatingTextEntity::SetFloatingTextInfo(const FFloatingTextCreationInfo& InInfo)
{
	FlyingText->SetText(InInfo.TextToDisplay);
	SetPositionInViewport(InInfo.RenderLocation, true);

	AddToViewport();
}