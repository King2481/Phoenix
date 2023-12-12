// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Phoenix/GameFramework/Reputation/ReputationInfo.h" // FFactionReputation
#include "ReputationComponent.generated.h"

class UFactionInfo;
class UReputationInfo;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHOENIX_API UReputationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UReputationComponent();

	UFUNCTION(BlueprintCallable, Category = "Reputation Component")
	void AddToReputation(UReputationInfo* InReputation);

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Reputation Component")
	TObjectPtr<UFactionInfo> CurrentFaction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Reputation Component")
	TArray<FFactionReputation> FactionReputation;
		
};
