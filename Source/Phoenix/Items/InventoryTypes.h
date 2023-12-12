// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "InventoryTypes.generated.h"

class UItemDataBase;

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UItemDataBase> Item;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Count;

	FInventoryItem()
	{
		Item = nullptr;
		Count = 1;
	}

	FInventoryItem(UItemDataBase* InItemData, const int32 InCount)
	{
		Item = InItemData;
		Count = InCount;
	}

	bool operator==(const FInventoryItem& Other) const
	{
		return Item == Other.Item;
	}

	explicit operator bool() const 
	{
		return Item != nullptr;
	}
};