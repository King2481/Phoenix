// Created by Bruce Crum.


#include "Phoenix/Player/PartyManagement.h"

// Sets default values for this component's properties
UPartyManagement::UPartyManagement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetComponentTickEnabled(false);

	MaxPartySize = 4;
}

bool UPartyManagement::AddCharacter(APhoenixCharacter* InCharacter)
{
	int32 AddedIndex = INDEX_NONE;

	if (!SpawnedPartyMembers.Contains(InCharacter))
	{
		AddedIndex = SpawnedPartyMembers.AddUnique(InCharacter);
		OnPartyChangedDelegate.Broadcast();
	}

	return AddedIndex != INDEX_NONE;
}

bool UPartyManagement::RemoveCharacter(APhoenixCharacter* CharacterToRemove)
{
	if (SpawnedPartyMembers.Contains(CharacterToRemove))
	{
		if (SpawnedPartyMembers.Remove(CharacterToRemove) > 0)
		{
			OnPartyChangedDelegate.Broadcast();
			return true;
		}
	}

	return false;
}

