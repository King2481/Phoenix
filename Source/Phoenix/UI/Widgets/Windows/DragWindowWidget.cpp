// Created by Bruce Crum.


#include "Phoenix/UI/Widgets/Windows/DragWindowWidget.h"

#include "Components/SizeBox.h"

UDragWindowWidget::UDragWindowWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SizeBox = nullptr;
	WidgetReference = nullptr;
}

void UDragWindowWidget::InitDragWindow(UUserWidget* InReferenceWidget)
{
	WidgetReference = InReferenceWidget;
	if (SizeBox)
	{
		const FVector2D Size = InReferenceWidget->GetDesiredSize();
		SizeBox->SetWidthOverride(Size.X);
		SizeBox->SetHeightOverride(Size.Y);
	}
}