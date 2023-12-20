// Created by Bruce Crum.


#include "Phoenix/UI/Widgets/Windows/DragableWindow.h"
#include "Phoenix/UI/Widgets/Windows/DragWindowWidget.h"
#include "Phoenix/UI/Widgets/Windows/WindowDragOperation.h"
#include "Phoenix/Settings/UIDeveloperSettings.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Kismet/KismetInputLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/SizeBox.h"

UDragableWindow::UDragableWindow()
{
	DragOffset = FVector2D::ZeroVector;
	SizeBox = nullptr;
	CloseButton = nullptr;
}

void UDragableWindow::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &ThisClass::OnClosedClicked);
	}
}

void UDragableWindow::NativeDestruct()
{
	Super::NativeDestruct();

	if (CloseButton)
	{
		CloseButton->OnClicked.RemoveDynamic(this, &ThisClass::OnClosedClicked);
	}
}

void UDragableWindow::OnClosedClicked()
{
	DeactivateWidget();
}

FReply UDragableWindow::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	DragOffset = USlateBlueprintLibrary::AbsoluteToLocal(InGeometry, UKismetInputLibrary::PointerEvent_GetScreenSpacePosition(InMouseEvent));

	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
}

void UDragableWindow::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (const auto UISettings = GetDefault<UUIDeveloperSettings>()) // Access via CDO
	{
		if (const auto Widget = CreateWidget<UDragWindowWidget>(this, UISettings->DefaultDragWidget.LoadSynchronous()))
		{
			Widget->InitDragWindow(this);

			if (const auto CanvasPanel = Cast<UCanvasPanel>(GetParent()))
			{
				CanvasPanel->SetVisibility(ESlateVisibility::Visible);
			}

			if (const auto OpAsWindowDrag = Cast<UWindowDragOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(UWindowDragOperation::StaticClass())))
			{
				OpAsWindowDrag->Pivot = EDragPivot::MouseDown;
				OpAsWindowDrag->DragOffset = DragOffset;
				OpAsWindowDrag->WidgetReference = this;
				OpAsWindowDrag->DefaultDragVisual = Widget;
				OpAsWindowDrag->OnDrop.AddDynamic(this, &ThisClass::OnWindowDrop);
				OutOperation = OpAsWindowDrag;
			}
		}
	}
}

void UDragableWindow::OnWindowDrop(UDragDropOperation* Operation)
{
	Operation->OnDrop.RemoveDynamic(this, &ThisClass::OnWindowDrop);
	ActivateWidget();
}