// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PhoenixGameModeBase.generated.h"

class UPhoenixAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class PHOENIX_API APhoenixGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	APhoenixGameModeBase();

	UFUNCTION(BlueprintCallable, Category = "Phoenix Game Mode Base")
	void OnEntityKilled(AActor* Victim, UPhoenixAbilitySystemComponent* KilledFrom);
	
};
