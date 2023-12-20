// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Phoenix/UI/Widgets/Windows/DragableWindow.h"
#include "LootWindow.generated.h"

struct FLootInfo;
struct FInventoryItem;
class UItemDataBase;
class UItemDisplayPanel;
class UInvetoryComponent;
class UButton;

/**
 * 
 */
UCLASS(BlueprintType)
class PHOENIX_API ULootWindow : public UDragableWindow
{
	GENERATED_BODY()

public:

	ULootWindow(const FObjectInitializer& ObjectInitializer);

	// UUserWidget interface
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized() override;
	// End of UUserWidget interface

	void HandleBackAction();

	// Data Table for the back button
	UPROPERTY(EditDefaultsOnly, Category = "Loot Window")
	FDataTableRowHandle BackInputActionData;

protected:

	UFUNCTION()
	void DisplayWindowAtLocation(const FLootInfo& NewInfo);

	UFUNCTION()
	void OnTakeAllClicked();
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Loot Window", meta = (BindWidget))
	TObjectPtr<UItemDisplayPanel> DisplayPanel;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Loot Window", meta = (BindWidget))
	TObjectPtr<UButton> TakeAllButton;

	UPROPERTY(BlueprintReadOnly, Category = "Loot Window")
	TObjectPtr<UInventoryComponent> LootingInventory;
};
