// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "LootDisplayPanel.generated.h"

class UCommonTileView;
struct FInventoryItem;

/**
 * 
 */
UCLASS(BlueprintType)
class PHOENIX_API ULootDisplayPanel : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	ULootDisplayPanel(const FObjectInitializer& ObjectInitializer);

	void RefreshItems(const TArray<FInventoryItem>& NewItems);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot Display Panel", meta = (BindWidget)  )
	TObjectPtr<UCommonTileView> TileView;
	
};
