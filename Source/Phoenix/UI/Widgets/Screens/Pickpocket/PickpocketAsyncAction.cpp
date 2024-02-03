// Created by Bruce Crum.


#include "Phoenix/UI/Widgets/Screens/Pickpocket/PickpocketAsyncAction.h"
#include "Phoenix/UI/Widgets/Screens/Pickpocket/PickpocketScreen.h"
#include "Phoenix/Settings/UIDeveloperSettings.h"

UPickpocketAsyncAction::UPickpocketAsyncAction()
{
	PickpocketScreenInstance = nullptr;
	PlayerController = nullptr;
}

UPickpocketAsyncAction* UPickpocketAsyncAction::DisplayPickpocketScreenAsync(UObject* WorldContextObject, APlayerController* ForPlayer, UInventoryComponent* PickpocketingFromInventory)
{
	UPickpocketAsyncAction* Action = NewObject<UPickpocketAsyncAction>();
	if (Action)
	{
		Action->PlayerController = ForPlayer;
		Action->Inventory = PickpocketingFromInventory;
	}

	return Action;
}

void UPickpocketAsyncAction::Activate()
{
	Super::Activate();

	if (const auto UISettings = GetDefault<UUIDeveloperSettings>()) // Access via CDO
	{
		if (PickpocketScreenInstance = CreateWidget<UPickpocketScreen>(PlayerController, UISettings->DefaultPickpocketScreen.LoadSynchronous()))
		{
			PickpocketScreenInstance->InitScreen(Inventory);
			PickpocketScreenInstance->AddToViewport();
			PickpocketScreenInstance->ActivateWidget();
		}
	}
}

void UPickpocketAsyncAction::CleanupAction()
{
	if (PickpocketScreenInstance)
	{

	}

	PickpocketScreenInstance = nullptr;
	PlayerController = nullptr;
	Inventory = nullptr;

	SetReadyToDestroy();
}