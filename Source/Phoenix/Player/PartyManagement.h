// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PartyManagement.generated.h"

class APhoenixCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPartyChangedDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHOENIX_API UPartyManagement : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UPartyManagement();

	UFUNCTION(BlueprintCallable, Category = "Party Management")
	bool AddCharacter(APhoenixCharacter* CharacterToAdd);

	UFUNCTION(BlueprintCallable, Category = "Party Management")
	bool RemoveCharacter(APhoenixCharacter* CharacterToRemove);

	UFUNCTION(BlueprintPure, Category = "Party Management")
	TArray<APhoenixCharacter*> GetPartyMembers() const { return SpawnedPartyMembers; }

	UFUNCTION(BlueprintPure, Category = "Party Management")
	uint8 GetMaxPartySize() const { return MaxPartySize; }

	UPROPERTY(BlueprintAssignable)
	FOnPartyChangedDelegate OnPartyChangedDelegate;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Party Management")
	TArray<TObjectPtr<APhoenixCharacter>> SpawnedPartyMembers;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Party Management")
	uint8 MaxPartySize;
};
