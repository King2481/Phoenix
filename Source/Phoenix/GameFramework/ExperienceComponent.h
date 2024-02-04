// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "ExperienceComponent.generated.h"

class UDataTable;

USTRUCT(BlueprintType)
struct FExperienceData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ExperienceRequired;

	// this specific constructor syntax is needed, otherwise there will be at least a warning, possibly an error when you package the project
	FExperienceData() : ExperienceRequired(0)
	{
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHOENIX_API UExperienceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UExperienceComponent();

	UFUNCTION(BlueprintCallable, Category = "Experience Component")
	void GainExperience(int32 ExperienceGained);

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Experience Component")
	TObjectPtr<UDataTable> ExperienceDataTable;

	UPROPERTY(BlueprintReadOnly, Category = "Experience Component", meta = (ClampMin = "0", UIMin = "0"))
	int32 TotalExperience;

	UPROPERTY(BlueprintReadOnly, Category = "Experience Component", meta = (ClampMin = "1", UIMin = "1"))
	uint8 CurrentLevel;

	UFUNCTION(BlueprintImplementableEvent, Category = "Experience Component")
	void BlueprintOnExperiencedGained(int32 ExperienceGained);

	UFUNCTION(BlueprintImplementableEvent, Category = "Experience Component")
	void BlueprintOnLevelUp(uint8 NewLevel);
		
};
