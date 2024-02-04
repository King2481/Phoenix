// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Phoenix/GameFramework/PhoenixTypes.h"
#include "Phoenix/GameFramework/Targeting/Targetable.h"
#include "Phoenix/Characters/Equipable.h"
#include "PhoenixCharacter.generated.h"

class UInventoryComponent;
class UPhoenixAbilitySystemComponent;
class UPhoenixGameplayAbility;
class UHealthComponent;
class UNameComponent;
class UTargetingComponent;
class UReputationComponent;
class UCombatFloatyNotification;

UCLASS()
class PHOENIX_API APhoenixCharacter : public ACharacter, public ITargetable, public IEquipable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APhoenixCharacter();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// The characters inventory component.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Phoenix Character")
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Phoenix Character")
	TObjectPtr<UPhoenixAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Phoenix Character")
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Phoenix Character")
	TObjectPtr<UNameComponent> NameComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Phoenix Character")
	TObjectPtr<UTargetingComponent> TargetingComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Phoenix Character")
	TObjectPtr<UReputationComponent> ReputationComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Phoenix Character")
	TObjectPtr<UCombatFloatyNotification> CombatFloatyNotification;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Phoenix Character")
	TSubclassOf<UPhoenixGameplayAbility> SneakAbility;

	UFUNCTION()
	void OnDeathEvent(const FOnDeathInfo& DeathInfo);

	// Called when the character actually dies.
	void OnDeath();

	// Blueprint event for when we die.
	UFUNCTION(BlueprintImplementableEvent, Category = "Phoenix Character")
	void BlueprintOnDeath();

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnSneakActivated();

	virtual FTargetableInfo GetTargetInfo_Implementation() const override;

	virtual USkeletalMeshComponent* GetEquipableAttachMesh_Implementation() const override { return GetMesh(); }
};
