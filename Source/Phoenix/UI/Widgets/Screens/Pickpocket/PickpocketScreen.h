// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Phoenix/UI/Widgets/PhoenixCommonActivatableWidget.h"
#include "PickPocketScreen.generated.h"

class UButton;
class UTextBlock;
class UItemDataBase;
class UItemDisplayPanel;
class UInventoryComponent;

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
	void UpdateSelectedItem(UItemDataBase* NewSlectedItem);

	void InitScreen(UInventoryComponent* InInventory);

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Pickpocket Screen", meta = (BindWidget))
	TObjectPtr<UButton> StealButton;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Pickpocket Screen", meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;

	UPROPERTY(BlueprintReadOnly, Category = "Pickpocket Screen", meta = (BindWidget))
	TObjectPtr<UTextBlock> PickpocketDCText;

	UPROPERTY(BlueprintReadOnly, Category = "Pickpocket Screen", meta = (BindWidget))
	TObjectPtr<UTextBlock> PickpocketRolledText;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Pickpocket Screen", meta = (BindWidget))
	TObjectPtr<UItemDisplayPanel> ItemDisplayPanel;

	UPROPERTY(BlueprintReadOnly, Category = "Pickpocket Screen")
	TObjectPtr<UItemDataBase> SelectedItem;

	UPROPERTY(BlueprintReadOnly, Category = "Pickpocket Screen")
	TObjectPtr<UInventoryComponent> Inventory;

	UFUNCTION()
	void OnStealButtonPressed();
	
	UFUNCTION()
	void OnCloseButtonPressed();

};
