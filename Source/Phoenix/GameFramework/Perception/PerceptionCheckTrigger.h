// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Engine/DataAsset.h"
#include "PerceptionCheckTrigger.generated.h"

class UMaterialInterface;

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class PHOENIX_API UPerceptionCheckTriggerBase : public UBoxComponent
{
	GENERATED_BODY()

public:

	UPerceptionCheckTriggerBase();

protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void OnTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void HandleOverlapedActor(AActor* OverlappedActor);

	virtual void OnPercievedSuccess(AActor* Perciever);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	uint8 DifficultyClassToPercieve;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	TObjectPtr<UPerceptionCheckResponse> PerceptionCheckResponse;

};

UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class PHOENIX_API UPerceptionCheckTriggerHighlightParent : public UPerceptionCheckTriggerBase
{
	GENERATED_BODY()

public:

	UPerceptionCheckTriggerHighlightParent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	bool bHiddenUntilPercieved;

protected:

	virtual void BeginPlay() override;

	virtual void OnPercievedSuccess(AActor* Perciever) override;


};

UCLASS()
class PHOENIX_API UPerceptionCheckResponse : public UDataAsset
{
	GENERATED_BODY()

public:

	UPerceptionCheckResponse();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Perception Check Response")
	bool bHighlightParent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Perception Check Response", meta = (EditCondition = "bHighlightsParent", EditConditionHides))
	TObjectPtr<UMaterialInterface> HighlightMaterial;


};