// Created by Bruce Crum.


#include "Phoenix/UI/Widgets/Screens/Pickpocket/PickpocketScreen.h"
#include "Phoenix/GameFramework/PhoenixGameplayStatics.h"
#include "Phoenix/Player/PhoenixPlayerController.h"
#include "Phoenix/Items/ItemDataBase.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

UPickpocketScreen::UPickpocketScreen()
{
	bSetVisibilityOnActivated = true;
	bSetVisibilityOnDeactivated = true;
	SetBindVisibilities(ESlateVisibility::Visible, ESlateVisibility::Collapsed, false);

	StealButton = nullptr;
	CloseButton = nullptr;
	PickpocketDCText = nullptr;
	PickpocketRolledText = nullptr;
	ItemDisplayPanel = nullptr;

	SelectedItem = nullptr;
	Inventory = nullptr;
}

void UPickpocketScreen::NativeConstruct()
{
	Super::NativeConstruct();

	if (StealButton)
	{
		StealButton->OnClicked.AddDynamic(this, &ThisClass::OnStealButtonPressed);
	}

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &ThisClass::OnCloseButtonPressed);
	}
}

void UPickpocketScreen::NativeDestruct()
{
	Super::NativeDestruct();

	if (StealButton)
	{
		StealButton->OnClicked.RemoveDynamic(this, &ThisClass::OnStealButtonPressed);
	}

	if (CloseButton)
	{
		CloseButton->OnClicked.RemoveDynamic(this, &ThisClass::OnCloseButtonPressed);
	}
}

void UPickpocketScreen::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	RemoveFromParent();

	if (const auto PC = Cast<APhoenixPlayerController>(GetOwningPlayer()))
	{
		PC->UpdateInputMode(EInputMode::GameAndUI);
	}
}

void UPickpocketScreen::InitScreen(UInventoryComponent* InInventory)
{
	Inventory = InInventory;
}

void UPickpocketScreen::OnStealButtonPressed()
{
	if (SelectedItem)
	{
		const FDiceRollToBeatResult Result = UPhoenixGameplayStatics::RollDiceToBeat({ FDiceRollInfo(EDiceType::D20) }, SelectedItem->PickpocketDifficultyClass);
	
		if (Result.bSuccessfullyPassed)
		{
			// Passed
		}
		else
		{
			if (true)
			{
				// Failed
			}
			else
			{
				// Caught
			}
		}
	}
}

void UPickpocketScreen::OnCloseButtonPressed()
{
	DeactivateWidget();
}

void UPickpocketScreen::UpdateSelectedItem(UItemDataBase* NewSelectedItem)
{
	SelectedItem = NewSelectedItem;

	if (SelectedItem)
	{
		PickpocketDCText->SetText(FText::FromString(FString::FromInt(SelectedItem->PickpocketDifficultyClass)));
		PickpocketDCText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		PickpocketDCText->SetVisibility(ESlateVisibility::Hidden);
	}
}