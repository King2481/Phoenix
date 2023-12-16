// Created by Bruce Crum.


#include "Phoenix/UI/Widgets/Windows/DragableWindow.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Kismet/KismetInputLibrary.h"

UDragableWindow::UDragableWindow()
{
	DragOffset = FVector2D::ZeroVector;
	SizeBox = nullptr;
}

FReply UDragableWindow::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	DragOffset = USlateBlueprintLibrary::AbsoluteToLocal(InGeometry, UKismetInputLibrary::PointerEvent_GetScreenSpacePosition(InMouseEvent));

	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
}

void UDragableWindow::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}