// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MouseWidget.generated.h"

class UMouseIconSet;
class UImage;
class UBorder;
class UTextBlock;

/**
 * 
 */
UCLASS()
class PHOENIX_API UMouseWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UMouseWidget(const FObjectInitializer& ObjectInitializer);
	
protected:

	UPROPERTY(BlueprintReadOnly, Category = "Mouse Widget", meta = (BindWidget))
	TObjectPtr<UImage> MouseIcon;

	UPROPERTY(BlueprintReadOnly, Category = "Mouse Widget", meta = (BindWidget))
	TObjectPtr<UBorder> TargetNameBorder;

	UPROPERTY(BlueprintReadOnly, Category = "Mouse Widget", meta = (BindWidget))
	TObjectPtr<UTextBlock> TargetNameText;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Mouse Widget")
	TObjectPtr<UMouseIconSet> DefaultMouseIconSet;

	TObjectPtr<UMouseIconSet> CurrentMouseIconSet;

	void UpdateMouseIcon(UMouseIconSet* NewIconSet);
	void UpdateMouseApperence();

	UFUNCTION()
	void OnTargetHighlighted(const FTargetableInfo& NewTargetInfo);

	UFUNCTION()
	void HandleMouseButtonDown(bool bIsDown);

	bool bIsClicking;

	// UUserWidget interface
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	// End of UUserWidget interface
	
};
