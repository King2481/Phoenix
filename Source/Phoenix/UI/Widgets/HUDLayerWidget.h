// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDLayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class PHOENIX_API UHUDLayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UHUDLayerWidget(const FObjectInitializer& ObjectInitializer);

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
};
