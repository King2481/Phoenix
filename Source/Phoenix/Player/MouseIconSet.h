// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MouseIconSet.generated.h"

/**
 * 
 */
UCLASS()
class PHOENIX_API UMouseIconSet : public UDataAsset
{
	GENERATED_BODY()

public:

	UMouseIconSet();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Mouse Icon Set")
	TObjectPtr<UTexture2D> DefaultTexture;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Mouse Icon Set")
	TObjectPtr<UTexture2D> ClickTexture;
	
};
