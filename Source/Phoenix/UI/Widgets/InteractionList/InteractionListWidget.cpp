// Created by Bruce Crum.


#include "Phoenix/UI/Widgets/InteractionList/InteractionListWidget.h"
#include "Phoenix/UI/Widgets/InteractionList/InteractionListEntryObject.h"
#include "Phoenix/Player/PhoenixPlayerController.h"

#include "Input/CommonUIInputTypes.h"
#include "Components/ListView.h"
#include "Components/CanvasPanelSlot.h"

UInteractionListWidget::UInteractionListWidget()
{
	ListView = nullptr;

	bSetVisibilityOnActivated = true;
	bSetVisibilityOnDeactivated = true;
	SetBindVisibilities(ESlateVisibility::SelfHitTestInvisible, ESlateVisibility::Collapsed, false);
}

void UInteractionListWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	RegisterUIActionBinding(FBindUIActionArgs(BackInputActionData, true, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleBackAction)));
}

void UInteractionListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (const auto PC = Cast<APhoenixPlayerController>(GetOwningPlayer()))
	{
		PC->OnDisplayAllInteractionsDelegate.AddDynamic(this, &ThisClass::DisplayItemsAtLocation);
	}
}

void UInteractionListWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (const auto PC = Cast<APhoenixPlayerController>(GetOwningPlayer()))
	{
		PC->OnDisplayAllInteractionsDelegate.RemoveDynamic(this, &ThisClass::DisplayItemsAtLocation);
	}
}

void UInteractionListWidget::HandleBackAction()
{
	DeactivateWidget();
}

void UInteractionListWidget::DisplayItemsAtLocation(const FPlayerInteractionsInfo& NewInfo)
{
	if (NewInfo.PossibleInteractions.Num() > 0)
	{	
		ActivateWidget();

		if (const auto CanvasPanelSlot = Cast<UCanvasPanelSlot>(Slot))
		{
			CanvasPanelSlot->SetPosition(NewInfo.RenderLocation);
		}

		ListView->ClearListItems();

		for (UInteractionData* Interaction : NewInfo.PossibleInteractions)
		{
			if (const auto ListEntryObject = NewObject<UInteractionListEntryObject>())
			{
				ListEntryObject->Init(Interaction, NewInfo.Target);
				ListView->AddItem(ListEntryObject);
			}
		}
	}
	else
	{
		if (IsActivated())
		{
			DeactivateWidget();
		}
	}
}