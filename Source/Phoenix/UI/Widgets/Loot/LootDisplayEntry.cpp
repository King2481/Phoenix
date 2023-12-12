// Created by Bruce Crum.


#include "Phoenix/UI/Widgets/Loot/LootDisplayEntry.h"
#include "Phoenix/UI/Widgets/Loot/LootEntryObject.h"

#include "Components/TextBlock.h"

ULootDisplayEntry::ULootDisplayEntry(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void ULootDisplayEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    if (const auto LootObject = Cast<ULootEntryObject>(ListItemObject))
    {
        if (AmountText)
        {
            if (LootObject->StoredItem.Count > 1)
            {
                AmountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
                AmountText->SetText(FText::FromString(FString::FromInt(LootObject->StoredItem.Count)));
            }
            else
            {
                AmountText->SetVisibility(ESlateVisibility::Collapsed);
            }
        }
    }
}