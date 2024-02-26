// Created by Bruce Crum.


#include "Phoenix/UI/Widgets/Items/ItemDisplayPanel.h"
#include "Phoenix/UI/Widgets/Items/ItemDisplayEntry.h"
#include "Phoenix/UI/Widgets/Items/ItemEntryObject.h"
#include "Phoenix/Items/InventoryComponent.h"

#include "CommonTileView.h"

UItemDisplayPanel::UItemDisplayPanel(const FObjectInitializer& ObjectInitializer)
{
    TileView = nullptr;
}

void UItemDisplayPanel::AddAllItemsFromInventory(UInventoryComponent* InInventory)
{
    if (TileView)
    {
        TileView->ClearListItems();
        
        for (const FInventoryItem& Item : InInventory->GetInventoryItems())
        {
            AddItemSingle(Item);
        }
    }
}

void UItemDisplayPanel::AddItemSingle(const FInventoryItem& NewItem)
{
    if (TileView)
    {
        if (const auto ListEntryObject = NewObject<UItemEntryObject>())
        {
            ListEntryObject->StoredItem = NewItem;
            TileView->AddItem(ListEntryObject);
        }
    }
}

void UItemDisplayPanel::RemoveItemSingle(UObject* ItemToRemove)
{
    if (TileView)
    {
        TileView->RemoveItem(ItemToRemove);
    }
}

void UItemDisplayPanel::ClearListItems()
{
    if (TileView)
    {
        TileView->ClearListItems();
    }
}

TArray<UUserWidget*> UItemDisplayPanel::GetPanelItems() const
{
    return TileView->GetDisplayedEntryWidgets();
}
