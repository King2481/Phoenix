// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "WorldDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(Config = World, defaultconfig, meta = (DisplayName = "World Developer Settings"))
class PHOENIX_API UWorldDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:


	UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category = "Phoenix World")
	TSoftClassPtr<AActor> FluidSimulationClass = nullptr;
	
};
