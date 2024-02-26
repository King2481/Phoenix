// Created by Bruce Crum.


#include "Phoenix/UI/Widgets/Items/ItemDisplayEntry.h"
#include "Phoenix/UI/Widgets/Items/ItemEntryObject.h"
#include "Phoenix/Items/InventoryComponent.h"

#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/ListView.h"

UItemDisplayEntry::UItemDisplayEntry(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    AmountText = nullptr;
    Background = nullptr;
    Highlight = nullptr;
    ItemImage = nullptr;
    ItemObject = nullptr;

    UnhoveredColor = FColor::Black;
    HoveredColor = FColor::Black;
    PressedColor = FColor::Black;

    bIsMouseButtonDownOnWidget = false;
}

void UItemDisplayEntry::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (Background)
    {
        Background->SetBrushColor(UnhoveredColor);
    }
}

void UItemDisplayEntry::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

    UpdateHoverStatus(true);
}

void UItemDisplayEntry::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseLeave(InMouseEvent);

    UpdateHoverStatus(false);
}

FReply UItemDisplayEntry::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    bIsMouseButtonDownOnWidget = true;
    UpdateHoverStatus(true);

    return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

FReply UItemDisplayEntry::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    bIsMouseButtonDownOnWidget = false;
    UpdateHoverStatus(true);

    return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

void UItemDisplayEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    if (ItemObject = Cast<UItemEntryObject>(ListItemObject))
    {
        if (AmountText)
        {
            if (ItemObject->StoredItem.Count > 1)
            {
                AmountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
                AmountText->SetText(FText::FromString(FString::FromInt(ItemObject->StoredItem.Count)));
            }
            else
            {
                AmountText->SetVisibility(ESlateVisibility::Collapsed);
            }
        }
    }
}

void UItemDisplayEntry::UpdateHoverStatus(bool bNewHover)
{
    if (bNewHover)
    {
        if (bIsMouseButtonDownOnWidget)
        {
            Background->SetBrushColor(PressedColor);
        }
        else
        {
            Background->SetBrushColor(HoveredColor);
        }
    }
    else
    {
        Background->SetBrushColor(UnhoveredColor);
    }
}

void UItemDisplayEntry::UpdateHighlightStatus(bool bNewHighlight)
{
    if (Highlight)
    {
        Highlight->SetVisibility(bNewHighlight ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }
}
