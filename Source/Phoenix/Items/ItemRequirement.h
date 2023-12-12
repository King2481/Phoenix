// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemRequirement.generated.h"

class UGameplayEffect;

/**
 * 
 */
UCLASS(Abstract, Blueprintable, EditInlineNew)
class PHOENIX_API UItemRequirement : public UObject
{
	GENERATED_BODY()

public:

	virtual bool MeetsRequirement() const { return true; }
	
};

UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Has Gameplay Effect"))
class UItemRequirementHasGameplayEffect : public UItemRequirement
{
	GENERATED_BODY()

public:

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Settings)
	TSubclassOf<UGameplayEffect> RequiredGameplayEffect = nullptr;

};