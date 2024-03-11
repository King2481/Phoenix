// Created by Bruce Crum.


#include "Phoenix/UI/Widgets/Screens/Pickpocket/PickpocketScreen.h"
#include "Phoenix/UI/Widgets/Items/ItemDisplayPanel.h"
#include "Phoenix/UI/Widgets/Items/ItemEntryObject.h"
#include "Phoenix/GameFramework/PhoenixGameplayStatics.h"
#include "Phoenix/Player/PhoenixPlayerController.h"
#include "Phoenix/Items/ItemDataBase.h"
#include "Phoenix/Items/InventoryComponent.h"

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
	CaughtSaveDCText = nullptr;
	PickpocketRolledText = nullptr;
	ItemDisplayPanel = nullptr;

	SelectedItem = nullptr;
	TargetInventory = nullptr;
	PocketerInventory = nullptr;
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

void UPickpocketScreen::InitScreen(UInventoryComponent* InTargetInventory, UInventoryComponent* InPocketerInventory)
{
	TargetInventory = InTargetInventory;
	PocketerInventory = InPocketerInventory;

	if (ItemDisplayPanel)
	{
		for (const FInventoryItem& Item : TargetInventory->GetInventoryItems())
		{
			if (Item.Item->bPickpocketable)
			{
				ItemDisplayPanel->AddItemSingle(Item);
			}
		}
	}
}

void UPickpocketScreen::OnStealButtonPressed()
{
	if (SelectedItem)
	{
		const UItemDataBase* Item = SelectedItem->StoredItem.Item;
		const FDiceRollToBeatResult Result = UPhoenixGameplayStatics::RollDiceToBeat({ FDiceRollInfo(EDiceType::D20) }, Item->PickpocketDifficultyClass);
	
		EPickpocketResult PickpocketResult = EPickpocketResult::Success;

		if (Result.bSuccessfullyPassed)
		{
			PickpocketRolledText->SetText(FText::FromString(FString::FromInt(Result.AmountRolled)));
		
			if (PocketerInventory->TransferItemBetweenInventories(SelectedItem->StoredItem, TargetInventory))
			{
				ItemDisplayPanel->RemoveItemSingle(SelectedItem);
			}
		}
		else
		{
			const FDiceRollToBeatResult Save = UPhoenixGameplayStatics::RollDiceToBeat({ FDiceRollInfo(EDiceType::D20) }, Item->PickpocketCaughtSaveDifficultyClass);
			
			// TODO: This is probably going to have to be a seperate text block as it does look confusing from a UI perspective why you could roll higher than
			// the pickpocket check but still "fail". But for MVP/Prototyping purposes, this is fine.

			PickpocketRolledText->SetText(FText::FromString(FString::FromInt(Save.AmountRolled)));

			if (Save.bSuccessfullyPassed)
			{
				PickpocketResult = EPickpocketResult::Failed;
			}
			else
			{
				PickpocketResult = EPickpocketResult::Caught;
			}
		}

		BlueprintPickpocketResult(PickpocketResult);
		OnPickpocketResult.Broadcast(PickpocketResult);
	}
}

void UPickpocketScreen::OnCloseButtonPressed()
{
	DeactivateWidget();
}

void UPickpocketScreen::UpdateSelectedItem(UItemEntryObject* NewSelectedItem)
{
	SelectedItem = NewSelectedItem;

	if (SelectedItem)
	{
		const UItemDataBase* Item = SelectedItem->StoredItem.Item;

		PickpocketDCText->SetText(FText::FromString(FString::FromInt(Item->PickpocketDifficultyClass)));
		PickpocketDCText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		CaughtSaveDCText->SetText(FText::FromString(FString::FromInt(Item->PickpocketCaughtSaveDifficultyClass)));
		CaughtSaveDCText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		PickpocketDCText->SetVisibility(ESlateVisibility::Hidden);
		CaughtSaveDCText->SetVisibility(ESlateVisibility::Hidden);
	}
}