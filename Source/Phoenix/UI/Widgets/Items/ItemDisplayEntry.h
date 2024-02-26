// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Phoenix/UI/Widgets/ToolTipWidget.h"
#include "Blueprint/IUserObjectListEntry.h" // IUserObjectListEntry
#include "ItemDisplayEntry.generated.h"

class UTextBlock;
class UBorder;
class UImage;
class UItemEntryObject;

/**
 * 
 */
UCLASS()
class PHOENIX_API UItemDisplayEntry : public UToolTipWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:

	UItemDisplayEntry(const FObjectInitializer& ObjectInitializer);

	virtual void NativePreConstruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UFUNCTION(BlueprintCallable, Category = "Item Display Entry")
	void UpdateHighlightStatus(bool bNewHighlight);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Item Display Entry", meta = (BindWidget))
	TObjectPtr<UTextBlock> AmountText;

	UPROPERTY(BlueprintReadOnly, Category = "Item Display Entry", meta = (BindWidget))
	TObjectPtr<UBorder> Background;

	UPROPERTY(BlueprintReadOnly, Category = "Item Display Entry", meta = (BindWidget))
	TObjectPtr<UBorder> Highlight;

	UPROPERTY(BlueprintReadOnly, Category = "Item Display Entry", meta = (BindWidget))
	TObjectPtr<UImage> ItemImage;

	UPROPERTY(BlueprintReadOnly, Category = "Item Display Entry")
	TObjectPtr<UItemEntryObject> ItemObject;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Display Entry")
	FLinearColor UnhoveredColor;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Display Entry")
	FLinearColor HoveredColor;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Display Entry")
	FLinearColor PressedColor;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	void UpdateHoverStatus(bool bNewHover);

	bool bIsMouseButtonDownOnWidget;
};
