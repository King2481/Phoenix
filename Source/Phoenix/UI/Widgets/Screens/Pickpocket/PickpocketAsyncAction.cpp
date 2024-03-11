// Created by Bruce Crum.


#include "Phoenix/UI/Widgets/Screens/Pickpocket/PickpocketAsyncAction.h"
#include "Phoenix/UI/Widgets/Screens/Pickpocket/PickpocketScreen.h"
#include "Phoenix/Settings/UIDeveloperSettings.h"

UPickpocketAsyncAction::UPickpocketAsyncAction()
{
	TargetInventory = nullptr;
	PocketerInventory = nullptr;

	PickpocketScreenInstance = nullptr;
	PlayerController = nullptr;
}

UPickpocketAsyncAction* UPickpocketAsyncAction::DisplayPickpocketScreenAsync(UObject* WorldContextObject, APlayerController* ForPlayer, UInventoryComponent* PickpocketingFromInventory, UInventoryComponent* InPocketerInventory)
{
	UPickpocketAsyncAction* Action = NewObject<UPickpocketAsyncAction>();
	if (Action)
	{
		Action->PlayerController = ForPlayer;
		Action->TargetInventory = PickpocketingFromInventory;
		Action->PocketerInventory = InPocketerInventory;
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
			PickpocketScreenInstance->InitScreen(TargetInventory, PocketerInventory);
			PickpocketScreenInstance->OnPickpocketResult.AddDynamic(this, &ThisClass::OnPickpocketResult);
			PickpocketScreenInstance->AddToViewport();
			PickpocketScreenInstance->ActivateWidget();
		}
	}
}

void UPickpocketAsyncAction::CleanupAction()
{
	if (PickpocketScreenInstance)
	{
		PickpocketScreenInstance->RemoveFromParent();
		PickpocketScreenInstance->OnPickpocketResult.RemoveDynamic(this, &ThisClass::OnPickpocketResult);
	}

	PickpocketScreenInstance = nullptr;
	PlayerController = nullptr;
	TargetInventory = nullptr;
	PocketerInventory = nullptr;

	SetReadyToDestroy();
}

void UPickpocketAsyncAction::OnPickpocketResult(EPickpocketResult Result)
{
	OnResultRecieved.Broadcast(Result);
}