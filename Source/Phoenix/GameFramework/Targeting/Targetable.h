// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Phoenix/GameFramework/Targeting/TargetingTypes.h"
#include "Targetable.generated.h"

class UInteractionData;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTargetable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PHOENIX_API ITargetable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Targetable")
	FTargetableInfo GetTargetInfo() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Targetable")
	TArray<UInteractionData*> GetPossibleInteractions() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Targetable")
	FMeshHighlightInfo GetMeshHighlightInfo() const;

};
