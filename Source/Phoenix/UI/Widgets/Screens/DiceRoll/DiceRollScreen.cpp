// Created by Bruce Crum.


#include "Phoenix/UI/Widgets/Screens/DiceRoll/DiceRollScreen.h"
#include "Phoenix/GameFramework/PhoenixGameplayStatics.h"
#include "Phoenix/Player/PhoenixPlayerController.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

UDiceRollScreen::UDiceRollScreen()
{
	bSetVisibilityOnActivated = true;
	bSetVisibilityOnDeactivated = true;
	SetBindVisibilities(ESlateVisibility::Visible, ESlateVisibility::Collapsed, false);

	RollDiceButton = nullptr;
	CancelButton = nullptr;
	ContinueButton = nullptr;
	DifficultyClassToBeatText = nullptr;
	DiceRollResultText = nullptr;

	DifficultyClass = 20;
}

void UDiceRollScreen::NativeConstruct()
{
	Super::NativeConstruct();

	if (RollDiceButton)
	{
		RollDiceButton->OnClicked.AddDynamic(this, &ThisClass::OnRollDiceClicked);
	}

	if (CancelButton)
	{
		CancelButton->OnClicked.AddDynamic(this, &ThisClass::OnCanceledClicked);
	}

	if (ContinueButton)
	{
		ContinueButton->OnClicked.AddDynamic(this, &ThisClass::OnContinueClicked);
	}
}

void UDiceRollScreen::NativeDestruct()
{
	Super::NativeDestruct();

	if (RollDiceButton)
	{
		RollDiceButton->OnClicked.RemoveDynamic(this, &ThisClass::OnRollDiceClicked);
	}

	if (CancelButton)
	{
		CancelButton->OnClicked.RemoveDynamic(this, &ThisClass::OnCanceledClicked);
	}

	if (ContinueButton)
	{
		ContinueButton->OnClicked.RemoveDynamic(this, &ThisClass::OnContinueClicked);
	}
}

void UDiceRollScreen::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	RemoveFromParent();

	if (const auto PC = Cast<APhoenixPlayerController>(GetOwningPlayer()))
	{
		PC->UpdateInputMode(EInputMode::GameAndUI);
	}
}

void UDiceRollScreen::OnRollDiceClicked()
{
	// Hiding of buttons
	{
		if (RollDiceButton)
		{
			RollDiceButton->SetVisibility(ESlateVisibility::Collapsed);
		}

		if (CancelButton)
		{
			CancelButton->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	// Actual dice rolling
	{
		const FDiceRollToBeatResult Result = UPhoenixGameplayStatics::RollDiceToBeat({ FDiceRollInfo(EDiceType::D20) }, DifficultyClass);

		if (DiceRollResultText)
		{
			DiceRollResultText->SetText(FText::FromString(FString::FromInt(Result.AmountRolled)));
		}

		BlueprintDiceRollResult(Result.bSuccessfullyPassed);

		OnDiceRollResult.Broadcast(Result.bSuccessfullyPassed);
	}
}

void UDiceRollScreen::OnCanceledClicked()
{
	DeactivateWidget();
}

void UDiceRollScreen::OnContinueClicked()
{
	DeactivateWidget();
}

void UDiceRollScreen::InitScreen(const FDiceRollScreenInfo& InInfo)
{
	if (CancelButton)
	{
		CancelButton->SetVisibility(InInfo.bCanCancel ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}

	DifficultyClass = InInfo.DifficultyClass;

	if (DifficultyClassToBeatText)
	{
		DifficultyClassToBeatText->SetText(FText::FromString(FString::FromInt(DifficultyClass)));
	}

	ActivateWidget();
}