// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatFloatyEntity.generated.h"

class UTextBlock;

USTRUCT()
struct FCombatFloatyCreationInfo
{
	GENERATED_BODY()

	UPROPERTY()
	FText TextToDisplay;

	UPROPERTY()
	FVector2D RenderLocation;

	FCombatFloatyCreationInfo()
	{
		TextToDisplay = FText::GetEmpty();
		RenderLocation = FVector2D::ZeroVector;
	}
};

/**
 * 
 */
UCLASS()
class PHOENIX_API UCombatFloatyEntity : public UUserWidget
{
	GENERATED_BODY()

public:

	UCombatFloatyEntity(const FObjectInitializer& ObjectInitializer);

	void SetCombatFloatyInfo(const FCombatFloatyCreationInfo& InInfo);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Combat Floaty Entity", meta = (BindWidget))
	TObjectPtr<UTextBlock> FlyingText;
	
};
