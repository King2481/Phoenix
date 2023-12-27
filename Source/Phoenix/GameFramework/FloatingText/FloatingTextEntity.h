// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FloatingTextEntity.generated.h"

class UTextBlock;

USTRUCT()
struct FFloatingTextCreationInfo
{
	GENERATED_BODY()

	UPROPERTY()
	FText TextToDisplay;

	UPROPERTY()
	FVector2D RenderLocation;

	FFloatingTextCreationInfo()
	{
		TextToDisplay = FText::GetEmpty();
		RenderLocation = FVector2D::ZeroVector;
	}
};

/**
 * 
 */
UCLASS()
class PHOENIX_API UFloatingTextEntity : public UUserWidget
{
	GENERATED_BODY()

public:

	UFloatingTextEntity(const FObjectInitializer& ObjectInitializer);

	void SetFloatingTextInfo(const FFloatingTextCreationInfo& InInfo);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Floating Text Entity", meta = (BindWidget))
	TObjectPtr<UTextBlock> FlyingText;
	
};
