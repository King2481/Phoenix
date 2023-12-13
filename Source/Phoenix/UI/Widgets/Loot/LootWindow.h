// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Phoenix/UI/Widgets/PhoenixCommonActivatableWidget.h"
#include "LootWindow.generated.h"

struct FLootInfo;
struct FInventoryItem;
class UItemDataBase;
class ULootDisplayPanel;

/**
 * 
 */
UCLASS(BlueprintType)
class PHOENIX_API ULootWindow : public UPhoenixCommonActivatableWidget
{
	GENERATED_BODY()

public:

	ULootWindow(const FObjectInitializer& ObjectInitializer);

	// UUserWidget interface
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized() override;
	// End of UUserWidget interface

	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;

	void HandleBackAction();

	// Data Table for the back button
	UPROPERTY(EditDefaultsOnly, Category = "Loot Window")
	FDataTableRowHandle BackInputActionData;

protected:

	UFUNCTION()
	void DisplayWindowAtLocation(const FLootInfo& NewInfo);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot Window", meta = (BindWidget))
	TObjectPtr<ULootDisplayPanel> DisplayPanel;
};
