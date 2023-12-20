// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragWindowWidget.generated.h"

class USizeBox;


/**
 * 
 */
UCLASS()
class PHOENIX_API UDragWindowWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UDragWindowWidget(const FObjectInitializer& ObjectInitializer);

	void InitDragWindow(UUserWidget* InReferenceWidget);

protected: 

	UPROPERTY(BlueprintReadOnly, Category = "Dragable Window Widget", meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox;

	TObjectPtr<UUserWidget> WidgetReference;
	
};
