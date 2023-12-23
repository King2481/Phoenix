// Created by Bruce Crum.


#include "Phoenix/UI/Widgets/CharacterMenu/CharacterMenu.h"
#include "Phoenix/Player/PhoenixPlayerController.h"

UCharacterMenu::UCharacterMenu()
{
	bSetVisibilityOnActivated = true;
	bSetVisibilityOnDeactivated = true;
	SetBindVisibilities(ESlateVisibility::Visible, ESlateVisibility::Collapsed, false);
}

void UCharacterMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (const auto PC = Cast<APhoenixPlayerController>(GetOwningPlayer()))
	{
		PC->OnCharacterMenuSelectedDelegate.AddDynamic(this, &ThisClass::OnCharacterMenuToggled);
	}
}

void UCharacterMenu::NativeDestruct()
{
	Super::NativeDestruct();

	if (const auto PC = Cast<APhoenixPlayerController>(GetOwningPlayer()))
	{
		PC->OnCharacterMenuSelectedDelegate.RemoveDynamic(this, &ThisClass::OnCharacterMenuToggled);
	}
}

void UCharacterMenu::OnCharacterMenuToggled()
{
	if (IsActivated())
	{
		DeactivateWidget();
	}
	else
	{
		ActivateWidget();
	}
}