// Created by Bruce Crum.


#include "Phoenix/UI/Widgets/Loot/LootDisplayPanel.h"
#include "Phoenix/UI/Widgets/Loot/LootDisplayEntry.h"
#include "Phoenix/UI/Widgets/Loot/LootEntryObject.h"

#include "CommonTileView.h"

ULootDisplayPanel::ULootDisplayPanel(const FObjectInitializer& ObjectInitializer)
{

}

void ULootDisplayPanel::RefreshItems(const TArray<FInventoryItem>& NewItems)
{
    if (TileView)
    {
        TileView->ClearListItems();

        for (const FInventoryItem& Item : NewItems)
        {
            if (const auto ListEntryObject = NewObject<ULootEntryObject>())
            {
                ListEntryObject->StoredItem = Item;
                TileView->AddItem(ListEntryObject);
            }
        }
    }
}
