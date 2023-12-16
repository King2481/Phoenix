// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "WindowDragOperation.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class PHOENIX_API UWindowDragOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:

	FVector2D DragOffset = FVector2D::ZeroVector;
	TObjectPtr<UUserWidget> WidgetReference;
	
};
