// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Blueprint/UserWidgetPool.h"
#include "CombatFloatyNotification.generated.h"

struct FHealthChangeInfo;
class UCombatFloatyEntity;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHOENIX_API UCombatFloatyNotification : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UCombatFloatyNotification();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called when the game ends or when game is not running
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void OnOwnersHealthChanged(const FHealthChangeResult& NewInfo);

	UPROPERTY()
	FUserWidgetPool CombatFloatyWidgetPool;

	UFUNCTION()
	void OnCombatFloatyAnimationFinished(UCombatFloatyEntity* Widget);

};
