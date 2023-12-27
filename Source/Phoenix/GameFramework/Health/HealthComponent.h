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

	FHealthTypeEntry()
	{
		HealthType = nullptr;
		Amount = 0;
	}

	FHealthTypeEntry(UHealthType* InHealthType, const int32 InAmount)
	{
		HealthType = InHealthType;
		Amount = InAmount;
	}

	bool operator==(const FHealthTypeEntry& Other) const
	{
		return HealthType == Other.HealthType;
	}
};

USTRUCT(BlueprintType)
struct FHealthChangeResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<FDamageInfo> DamageSources;

	FHealthChangeResult()
	{

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

	UFUNCTION()
	void OnHealthUpdatedEvent(const FModifyHealthInfo& ModifyHealthInfo);

	UPROPERTY(BlueprintAssignable)
	FOnDeathDelegate OnDeathDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedDelegate OnHealthChangedDelegate;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Health Component")
	TArray<FHealthTypeEntry> HealthEntrys;

	static bool SortHealthTypePriority(const FHealthTypeEntry& EntryA, const FHealthTypeEntry& EntryB)
	{
		return EntryA.HealthType->Priority > EntryB.HealthType->Priority;
	}

};
