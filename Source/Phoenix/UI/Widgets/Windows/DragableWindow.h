// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Phoenix/UI/Widgets/PhoenixCommonActivatableWidget.h"
#include "DragableWindow.generated.h"

class USizeBox;
class UButton;

/**
 * 
 */
UCLASS()
class PHOENIX_API UDragableWindow : public UPhoenixCommonActivatableWidget
{
	GENERATED_BODY()

public:

	UDragableWindow();

protected:

	// UUserWidget interface
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	// End of UUserWidget interface

	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;

	UFUNCTION()
	void OnWindowDrop(UDragDropOperation* Operation);

	UFUNCTION()
	void OnClosedClicked();

	UPROPERTY(BlueprintReadOnly, Category = "Dragable Window")
	FVector2D DragOffset;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Dragable Window", meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Dragable Window", meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;
	
};
