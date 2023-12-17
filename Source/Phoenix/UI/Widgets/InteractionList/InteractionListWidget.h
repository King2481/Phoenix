// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Phoenix/UI/Widgets/PhoenixCommonActivatableWidget.h"
#include "Phoenix/Player/PhoenixPlayerController.h" // TODO: For FPlayerInteractionsInfo struct, move struct out when possible.
#include "InteractionListWidget.generated.h"

class UListView;

/**
 * 
 */
UCLASS()
class PHOENIX_API UInteractionListWidget : public UPhoenixCommonActivatableWidget
{
	GENERATED_BODY()

public:

	UInteractionListWidget();

	// UUserWidget interface
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized() override;
	// End of UUserWidget interface

protected:

	void HandleBackAction();

	// Data Table for the back button
	UPROPERTY(EditDefaultsOnly, Category = "Interaction List")
	FDataTableRowHandle BackInputActionData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction List", meta = (BindWidget))
	TObjectPtr<UListView> ListView;

	UFUNCTION()
	void DisplayItemsAtLocation(const FPlayerInteractionsInfo& NewInfo);

	UFUNCTION()
	void OnListItemClicked(UObject* Object);
	
};
