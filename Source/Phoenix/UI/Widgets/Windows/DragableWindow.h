// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Phoenix/UI/Widgets/PhoenixCommonActivatableWidget.h"
#include "DragableWindow.generated.h"

class USizeBox;

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

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	FVector2D DragOffset;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Dragable Window", meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox;
	
};
