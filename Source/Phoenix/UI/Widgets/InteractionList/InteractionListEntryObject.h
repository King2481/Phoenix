// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InteractionListEntryObject.generated.h"

class UInteractionData;
class UPhoenixAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class PHOENIX_API UInteractionListEntryObject : public UObject
{
	GENERATED_BODY()

public:

	UInteractionListEntryObject();

	void Init(UInteractionData* InInteraction, UPhoenixAbilitySystemComponent* InTarget);

	UPROPERTY(BlueprintReadOnly, Category = "Interaction List Entry Object")
	TObjectPtr<UInteractionData> Interaction;

	UPROPERTY(BlueprintReadOnly, Category = "Interaction List Entry Object")
	TObjectPtr<UPhoenixAbilitySystemComponent> Target;
};
