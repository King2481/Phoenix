// Created by Bruce Crum.


#include "Phoenix/UI/Widgets/HUDLayerWidget.h"
#include "Phoenix/UI/Widgets/Windows/WindowDragOperation.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Kismet/KismetInputLibrary.h"

UHUDLayerWidget::UHUDLayerWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

bool UHUDLayerWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (const auto WindowDragOp = Cast<UWindowDragOperation>(InOperation))
	{
		WindowDragOp->WidgetReference->RemoveFromParent();

		if (const auto CanvasPanel = Cast<UCanvasPanel>(GetRootWidget()))
		{
			CanvasPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			CanvasPanel->AddChild(WindowDragOp->WidgetReference);
			WindowDragOp->WidgetReference->AddToViewport();

			if (const auto AsCanvasSlot = Cast<UCanvasPanelSlot>(WindowDragOp->WidgetReference->Slot))
			{
				const FVector2D ToLocal = USlateBlueprintLibrary::AbsoluteToLocal(InGeometry, UKismetInputLibrary::PointerEvent_GetScreenSpacePosition(InDragDropEvent));

				AsCanvasSlot->SetAutoSize(true);
				AsCanvasSlot->SetPosition(ToLocal - WindowDragOp->DragOffset);

				return true;
			}
		}
	}

	return false;
}