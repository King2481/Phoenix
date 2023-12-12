// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHOENIX_API UTargetingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UTargetingComponent();

protected:

	UFUNCTION()
	void OnBeginCursorOver(AActor* TouchedActor);

	UFUNCTION()
	void OnEndCursorOver(AActor* TouchedActor);

	UFUNCTION()
	void OnClicked(AActor* TouchedActor, FKey ButtonPressed);

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
		
};
