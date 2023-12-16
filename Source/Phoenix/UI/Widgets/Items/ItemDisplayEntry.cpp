// Created by Bruce Crum.


#include "Phoenix/UI/Widgets/Items/ItemDisplayEntry.h"
#include "Phoenix/UI/Widgets/Items/ItemEntryObject.h"
#include "Phoenix/Items/InventoryComponent.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ListView.h"

UItemDisplayEntry::UItemDisplayEntry(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    AmountText = nullptr;
    ItemObject = nullptr;
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