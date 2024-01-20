// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SurfaceReactionData.generated.h"

class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FPhysicalSurfaceReactionData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<USoundBase> ReactionSound;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<UNiagaraSystem> ReactionFX;

	FPhysicalSurfaceReactionData()
	{
		ReactionSound = nullptr;
		ReactionFX = nullptr;
	}

	explicit operator bool() const
	{
		return ReactionSound != nullptr || ReactionFX != nullptr;
	}
};

/**
 * 
 */
UCLASS()
class PHOENIX_API USurfaceReactionData : public UDataAsset
{
	GENERATED_BODY()

public:

	USurfaceReactionData();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Surface Reaction Data")
	TMap<TEnumAsByte<EPhysicalSurface>, FPhysicalSurfaceReactionData> SurfaceToReactionDataMap;

	
};
