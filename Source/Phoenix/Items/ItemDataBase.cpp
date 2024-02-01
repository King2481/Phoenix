// Created by Bruce Crum.


#include "Phoenix/Items/ItemDataBase.h"

UItemDataBase::UItemDataBase()
{
	ItemName = FText::GetEmpty();
	ItemDescription = FText::GetEmpty();
	bStackable = true;
	MaximumAmount = 99;
	ItemCategory = nullptr;
	ItemQuality = nullptr;
	InventoryItemTexture = nullptr;
	bPickpocketable = true;
	PickpocketDifficultyClass = 8;
}