// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "ItemDisplayPanel.generated.h"

class UCommonTileView;
class UInventoryComponent;
struct FInventoryItem;

/**
 * 
 */
UCLASS(BlueprintType)
class PHOENIX_API UItemDisplayPanel : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	UItemDisplayPanel(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Item Display Panel")
	void AddAllItemsFromInventory(UInventoryComponent* InInventory);

	UFUNCTION(BlueprintCallable, Category = "Item Display Panel")
	void AddItemSingle(const FInventoryItem& NewItem);

	UFUNCTION(BlueprintCallable, Category = "Item Display Panel")
	void RemoveItemSingle(UObject* ItemToRemove);

	void ClearListItems();

	TArray<UUserWidget*> GetPanelItems() const;

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item Display Panel", meta = (BindWidget)  )
	TObjectPtr<UCommonTileView> TileView;
	
};
