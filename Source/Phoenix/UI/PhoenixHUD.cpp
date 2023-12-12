// Created by Bruce Crum.


#include "Phoenix/UI/PhoenixHUD.h"

#include "Blueprint/UserWidget.h"

APhoenixHUD::APhoenixHUD()
{

}

void APhoenixHUD::BeginPlay()
{
	Super::BeginPlay();

	for (FWidgetCreationInfo WidgetInfo : WidgetsToCreate)
	{
		if (WidgetInfo.WidgetClass)
		{
			if (const auto Widget = CreateWidget<UUserWidget>(GetOwningPlayerController(), WidgetInfo.WidgetClass))
			{
				Widget->AddToViewport(WidgetInfo.ZOrder);
				InstancedWidgets.AddUnique(Widget);
			}
		}
	}
}

void APhoenixHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (int i = InstancedWidgets.Num() - 1; i >= 0; i--)
	{
		if (UUserWidget* Widget = InstancedWidgets[i])
		{
			InstancedWidgets.RemoveSingle(Widget);
			Widget->RemoveFromParent();
		}
	}

	InstancedWidgets.Empty();

	Super::EndPlay(EndPlayReason);
}
