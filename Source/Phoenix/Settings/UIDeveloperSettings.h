// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UIDeveloperSettings.generated.h"

class UMouseIconSet;

/**
 * 
 */
UCLASS(Config = UI, defaultconfig, meta = (DisplayName = "UI Developer Settings"))
class PHOENIX_API UUIDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category = "Phoenix UI")
	TSoftObjectPtr<UMouseIconSet> DefaultMouseIconSet = nullptr;

	UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category = "Phoenix UI")
	TSoftClassPtr<UUserWidget> DefaultDragWidget = nullptr;

};
