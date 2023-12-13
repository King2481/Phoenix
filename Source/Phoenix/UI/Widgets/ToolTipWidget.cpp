// Created by Bruce Crum.


#include "Phoenix/UI/Widgets/ToolTipWidget.h"

UToolTipWidget::UToolTipWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ToolTipClassToUse = nullptr;
}

void UToolTipWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ToolTipClassToUse != nullptr)
	{
		if (const auto InstancedToolTip = CreateWidget<UUserWidget>(this, ToolTipClassToUse))
		{
			SetToolTip(InstancedToolTip);
		}
	}
}