// Created by Bruce Crum.


#include "Phoenix/UI/Widgets/Screens/DiceRoll/DiceRollAsyncAction.h"
#include "Phoenix/UI/Widgets/Screens/DiceRoll/DiceRollScreen.h"
#include "Phoenix/Settings/UIDeveloperSettings.h"

#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

UDiceRollAsyncAction::UDiceRollAsyncAction()
{
	DiceRollScreenInfo = FDiceRollScreenInfo();

	DiceRollScreenInstance = nullptr;
	PlayerController = nullptr;
}

UDiceRollAsyncAction* UDiceRollAsyncAction::DisplayDiceRollScreenAsync(UObject* WorldContextObject, APlayerController* ForPlayer, const FDiceRollScreenInfo& InDiceRollScreenInfo)
{
	UDiceRollAsyncAction* Action = NewObject<UDiceRollAsyncAction>();
	if (Action)
	{
		Action->DiceRollScreenInfo = InDiceRollScreenInfo;
		Action->PlayerController = ForPlayer;
	}

	return Action;
}

void UDiceRollAsyncAction::Activate()
{
	Super::Activate();

	if (const auto UISettings = GetDefault<UUIDeveloperSettings>()) // Access via CDO
	{
		if (DiceRollScreenInstance = CreateWidget<UDiceRollScreen>(PlayerController, UISettings->DefaultDiceRollScreen.LoadSynchronous()))
		{
			DiceRollScreenInstance->AddToViewport();
			DiceRollScreenInstance->OnDiceRollResult.AddDynamic(this, &ThisClass::OnDiceRollResult);
			DiceRollScreenInstance->ContinueButton->OnClicked.AddDynamic(this, &ThisClass::OnScreenClose);
			DiceRollScreenInstance->CancelButton->OnClicked.AddDynamic(this, &ThisClass::OnDiceRollCanceled);
			DiceRollScreenInstance->InitScreen(DiceRollScreenInfo);
		}
	}
}

void UDiceRollAsyncAction::OnDiceRollResult(bool bSuccess)
{
	if (bSuccess)
	{
		OnSuccess.Broadcast();
	}
	else
	{
		OnFail.Broadcast();
	}
}

void UDiceRollAsyncAction::OnDiceRollCanceled()
{
	OnCanceled.Broadcast();
	CleanupAction();
}

void UDiceRollAsyncAction::OnScreenClose()
{
	CleanupAction();

	OnClose.Broadcast();
}

void UDiceRollAsyncAction::CleanupAction()
{
	if (DiceRollScreenInstance)
	{
		DiceRollScreenInstance->OnDiceRollResult.RemoveDynamic(this, &ThisClass::OnDiceRollResult);
		DiceRollScreenInstance->ContinueButton->OnClicked.RemoveDynamic(this, &ThisClass::OnScreenClose);
		DiceRollScreenInstance->CancelButton->OnClicked.RemoveDynamic(this, &ThisClass::OnDiceRollCanceled);
	}

	DiceRollScreenInfo = FDiceRollScreenInfo();
	DiceRollScreenInstance = nullptr;
	PlayerController = nullptr;

	SetReadyToDestroy();
}
