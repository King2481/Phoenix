// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Phoenix/UI/Widgets/PhoenixCommonActivatableWidget.h"
#include "Phoenix/GameFramework/PhoenixTypes.h"
#include "DiceRollScreen.generated.h"

class UButton;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDiceRollScreenResultDelegate, bool, bSuccess);

/**
 * 
 */
UCLASS()
class PHOENIX_API UDiceRollScreen : public UPhoenixCommonActivatableWidget
{
	GENERATED_BODY()

public:

	UDiceRollScreen();

	// UUserWidget interface
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	// End of UUserWidget interface

	virtual void NativeOnDeactivated() override;

	void InitScreen(const FDiceRollScreenInfo& InInfo);

	UPROPERTY(BlueprintAssignable)
	FDiceRollScreenResultDelegate OnDiceRollResult;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Dice Roll Screen", meta = (BindWidget))
	TObjectPtr<UButton> CancelButton;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Dice Roll Screen", meta = (BindWidget))
	TObjectPtr<UButton> ContinueButton;

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Dice Roll Screen", meta = (BindWidget))
	TObjectPtr<UButton> RollDiceButton;

	UPROPERTY(BlueprintReadOnly, Category = "Dice Roll Screen", meta = (BindWidget))
	TObjectPtr<UTextBlock> DifficultyClassToBeatText;

	UPROPERTY(BlueprintReadOnly, Category = "Dice Roll Screen", meta = (BindWidget))
	TObjectPtr<UTextBlock> ResultText;

	UPROPERTY(BlueprintReadOnly, Category = "Dice Roll Screen")
	uint8 DifficultyClass;

	UFUNCTION()
	void OnRollDiceClicked();

	UFUNCTION()
	void OnCanceledClicked();

	UFUNCTION()
	void OnContinueClicked();

	UFUNCTION(BlueprintImplementableEvent, Category = "Dice Roll Screen")
	void BlueprintDiceRollResult(bool bSuccess);

	
};
