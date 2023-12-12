// Copyright Epic Games, Inc. All Rights Reserved.


#include "PhoenixGameModeBase.h"
#include "Phoenix/GameModes/PhoenixGameState.h"

APhoenixGameModeBase::APhoenixGameModeBase()
{
	GameStateClass = APhoenixGameState::StaticClass();
}

void APhoenixGameModeBase::OnEntityKilled(AActor* Victim, UPhoenixAbilitySystemComponent* KilledFrom)
{

}