// Created by Bruce Crum.


#include "Phoenix/UI/Widgets/Loot/LootWindow.h"
#include "Phoenix/UI/Widgets/Items/ItemDisplayPanel.h"
#include "Phoenix/UI/Widgets/Items/ItemDisplayEntry.h"
#include "Phoenix/Player/PhoenixPlayerController.h"
#include "Phoenix/Items/InventoryComponent.h"

#include "Input/CommonUIInputTypes.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"

ULootWindow::ULootWindow(const FObjectInitializer& ObjectInitializer)
{
	bSetVisibilityOnActivated = true;
	bSetVisibilityOnDeactivated = true;
	SetBindVisibilities(ESlateVisibility::SelfHitTestInvisible, ESlateVisibility::Collapsed, false);

	DisplayPanel = nullptr;
	TakeAllButton = nullptr;
	LootingInventory = nullptr;
}

void ULootWindow::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	RegisterUIActionBinding(FBindUIActionArgs(BackInputActionData, true, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleBackAction)));
}

void ULootWindow::NativeConstruct()
{
	Super::NativeConstruct();

	if (const auto PC = Cast<APhoenixPlayerController>(GetOwningPlayer()))
	{
		PC->OnDisplayLootWindowDelegate.AddDynamic(this, &ThisClass::DisplayWindowAtLocation);
	}

	if (TakeAllButton)
	{
		TakeAllButton->OnClicked.AddDynamic(this, &ThisClass::OnTakeAllClicked);
	}
}

void ULootWindow::NativeDestruct()
{
	Super::NativeDestruct();

	if (const auto PC = Cast<APhoenixPlayerController>(GetOwningPlayer()))
	{
		PC->OnDisplayLootWindowDelegate.RemoveDynamic(this, &ThisClass::DisplayWindowAtLocation);
	}

	if (TakeAllButton)
	{
		TakeAllButton->OnClicked.RemoveDynamic(this, &ThisClass::OnTakeAllClicked);
	}
}

void ULootWindow::NativeOnActivated()
{
	Super::NativeOnActivated();

	if (const auto PC = Cast<APhoenixPlayerController>(GetOwningPlayer()))
	{
		PC->UpdateInputMode(EInputMode::GameAndUI);
	}
}

void ULootWindow::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	if (const auto PC = Cast<APhoenixPlayerController>(GetOwningPlayer()))
	{
		PC->UpdateInputMode(EInputMode::GameAndUI);
	}

	LootingInventory = nullptr;
}

void ULootWindow::HandleBackAction()
{
	DeactivateWidget();
}

void ULootWindow::DisplayWindowAtLocation(const FLootInfo& NewInfo)
{
	ActivateWidget();

	if (const auto CanvasPanelSlot = Cast<UCanvasPanelSlot>(Slot))
	{
		CanvasPanelSlot->SetPosition(NewInfo.RenderLocation);
	}

	LootingInventory = NewInfo.Inventory;

	if (DisplayPanel)
	{
		DisplayPanel->RefreshItems(NewInfo.Inventory);
	}
}

void ULootWindow::OnTakeAllClicked()
{
	if (DisplayPanel)
	{
		if (const auto PC = Cast<APhoenixPlayerController>(GetOwningPlayer()))
		{
			// TODO: I wonder if this should be an interface call.
			if (const auto Inventory = PC->GetPawn()->GetComponentByClass<UInventoryComponent>())
			{
				Inventory->AttemptToTransferAllItemBetweenInventories(LootingInventory);

				DisplayPanel->ClearListItems();
				DeactivateWidget();
			}
		}
	}
}