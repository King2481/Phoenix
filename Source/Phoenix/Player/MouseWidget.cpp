// Created by Bruce Crum.


#include "Phoenix/Player/MouseWidget.h"
#include "Phoenix/Player/MouseIconSet.h"
#include "Phoenix/Player/PhoenixPlayerController.h"
#include "Phoenix/Settings/UIDeveloperSettings.h"
#include "Phoenix/GameFramework/Targeting/InteractionData.h"

#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"

UMouseWidget::UMouseWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultMouseIconSet = nullptr;
	CurrentMouseIconSet = nullptr;
	bIsClicking = false;
}

void UMouseWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (const auto UISettings = GetDefault<UUIDeveloperSettings>()) // Access via CDO
	{
		DefaultMouseIconSet = UISettings->DefaultMouseIconSet.LoadSynchronous();
		UpdateMouseIcon(DefaultMouseIconSet);
	}
}

void UMouseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (const auto PC = Cast<APhoenixPlayerController>(GetOwningPlayer()))
	{
		PC->OnPlayerTargetChangedDelegate.AddDynamic(this, &ThisClass::OnTargetHighlighted);
		PC->OnSelectPressedDelegate.AddDynamic(this, &ThisClass::HandleMouseButtonDown);
	}
}

void UMouseWidget::NativeDestruct()
{
	if (const auto PC = Cast<APhoenixPlayerController>(GetOwningPlayer()))
	{
		PC->OnPlayerTargetChangedDelegate.RemoveDynamic(this, &ThisClass::OnTargetHighlighted);
		PC->OnSelectPressedDelegate.RemoveDynamic(this, &ThisClass::HandleMouseButtonDown);
	}

	Super::NativeDestruct();
}

void UMouseWidget::OnTargetHighlighted(const FTargetableInfo& NewTargetInfo)
{
	if (!NewTargetInfo.PossibleInteractions.IsEmpty())
	{
		TargetNameBorder->SetVisibility(ESlateVisibility::HitTestInvisible);
		TargetNameText->SetText(NewTargetInfo.TargetName);

		UpdateMouseIcon(NewTargetInfo.PossibleInteractions[0]->MouseIconSet);
	}
	else
	{
		TargetNameBorder->SetVisibility(ESlateVisibility::Hidden);
		UpdateMouseIcon(DefaultMouseIconSet);
	}
}

void UMouseWidget::UpdateMouseIcon(UMouseIconSet* NewIconSet)
{
	CurrentMouseIconSet = NewIconSet;
	UpdateMouseApperence();
}

void UMouseWidget::HandleMouseButtonDown(bool bIsDown)
{
	bIsClicking = bIsDown;
	UpdateMouseApperence();
}

void UMouseWidget::UpdateMouseApperence()
{
	if (CurrentMouseIconSet)
	{
		UTexture2D* Texture = bIsClicking ? CurrentMouseIconSet->ClickTexture : CurrentMouseIconSet->DefaultTexture;
		if (MouseIcon)
		{
			MouseIcon->SetBrushFromTexture(Texture, true);
		}
	}
}