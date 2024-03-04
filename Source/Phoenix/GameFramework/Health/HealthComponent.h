// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Phoenix/GameFramework/Health/HealthType.h"
#include "Phoenix/Abilities/AbilityTypes.h"
#include "Phoenix/GameFramework/PhoenixTypes.h"
#include "HealthComponent.generated.h"

class UHealthType;

USTRUCT(BlueprintType)
struct FHealthTypeEntry
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TObjectPtr<UHealthType> HealthType;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 Amount;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 MaxAmount;

	FHealthTypeEntry()
	{
		HealthType = nullptr;
		Amount = 0;
		MaxAmount = 0;
	}

	FHealthTypeEntry(UHealthType* InHealthType, const int32 InAmount, const int32 InMaxAmount)
	{
		HealthType = InHealthType;
		Amount = InAmount;
		MaxAmount = InMaxAmount;
	}

	bool operator==(const FHealthTypeEntry& Other) const
	{
		return HealthType == Other.HealthType;
	}

	bool operator<(const FHealthTypeEntry& Other) const
	{
		return HealthType->Priority > Other.HealthType->Priority;
	}
};

USTRUCT(BlueprintType)
struct FHealthChangeResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<FDamageInfo> DamageSources;

	UPROPERTY(BlueprintReadOnly)
	TArray<FHealthTypeEntry> CurrentHealthPools;

	UPROPERTY(BlueprintReadOnly)
	float HealthRemainingAsRatio;

	FHealthChangeResult()
	{
		HealthRemainingAsRatio = 0.0f;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathDelegate, const FOnDeathInfo&, NewDeathInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedDelegate, const FHealthChangeResult&, NewHealthInfo);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHOENIX_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the game ends or when game is not running
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category = "Health Component")
	void AddHealthTypeEntry(const FHealthTypeEntry& HealthTypeToAdd);

	UFUNCTION(BlueprintCallable, Category = "Health Component")
	void RemoveHealthTypeEntry(const FHealthTypeEntry& HealthTypeToRemove);

	UFUNCTION(BlueprintPure, Category = "Health Component")
	TArray<FHealthTypeEntry> GetHealthTypeEntries() const { return HealthEntrys; }

	UFUNCTION(BlueprintPure, Category = "Health Component")
	float GetHealthRemainingAsRatio() const;

	UFUNCTION()
	void OnHealthUpdatedEvent(const FModifyHealthInfo& ModifyHealthInfo);

	UPROPERTY(BlueprintAssignable)
	FOnDeathDelegate OnDeathDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedDelegate OnHealthChangedDelegate;

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Health Component")
	TArray<FHealthTypeEntry> DefaultHealthEntrys;

	UPROPERTY(BlueprintReadOnly, Category = "Health Component")
	TArray<FHealthTypeEntry> HealthEntrys;

};
