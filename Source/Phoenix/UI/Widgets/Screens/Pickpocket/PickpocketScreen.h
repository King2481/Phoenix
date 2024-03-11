// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Phoenix/UI/Widgets/PhoenixCommonActivatableWidget.h"
#include "Phoenix/GameFramework/PhoenixTypes.h"
#include "PickPocketScreen.generated.h"

class UButton;
class UTextBlock;
class UItemDataBase;
class UItemDisplayPanel;
class UInventoryComponent;
class UItemEntryObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPickpocketResultDelegate, EPickpocketResult, Result);

/**
 * 
 */
UCLASS()
class PHOENIX_API UPickpocketScreen : public UPhoenixCommonActivatableWidget
{
	GENERATED_BODY()

public:

	UPickpocketScreen();

	// UUserWidget interface
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	// End of UUserWidget interface

	virtual void NativeOnDeactivated() override;

	UFUNCTION(BlueprintCallable, Category = "Pickpocket Screen")
	void UpdateSelectedItem(UItemEntryObject* NewSlectedItem);

	void InitScreen(UInventoryComponent* InTargetInventory, UInventoryComponent* InPocketInventory);

	UPROPERTY(BlueprintAssignable)
	FPickpocketResultDelegate OnPickpocketResult;

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Pickpocket Screen", meta = (BindWidget))
	TObjectPtr<UButton> StealButton;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Pickpocket Screen", meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;

	UPROPERTY(BlueprintReadOnly, Category = "Pickpocket Screen", meta = (BindWidget))
	TObjectPtr<UTextBlock> PickpocketDCText;

	UPROPERTY(BlueprintReadOnly, Category = "Pickpocket Screen", meta = (BindWidget))
	TObjectPtr<UTextBlock> CaughtSaveDCText;

	UPROPERTY(BlueprintReadOnly, Category = "Pickpocket Screen", meta = (BindWidget))
	TObjectPtr<UTextBlock> PickpocketRolledText;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Pickpocket Screen", meta = (BindWidget))
	TObjectPtr<UItemDisplayPanel> ItemDisplayPanel;

	UPROPERTY(BlueprintReadOnly, Category = "Pickpocket Screen")
	TObjectPtr<UItemEntryObject> SelectedItem;

	UPROPERTY(BlueprintReadOnly, Category = "Pickpocket Screen")
	TObjectPtr<UInventoryComponent> TargetInventory;

	UPROPERTY(BlueprintReadOnly, Category = "Pickpocket Screen")
	TObjectPtr<UInventoryComponent> PocketerInventory;

	UFUNCTION()
	void OnStealButtonPressed();
	
	UFUNCTION()
	void OnCloseButtonPressed();

	UFUNCTION(BlueprintImplementableEvent, Category = "Pickpocket Screen")
	void BlueprintPickpocketResult(EPickpocketResult Result);

};
