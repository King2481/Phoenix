// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Launchable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULaunchable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PHOENIX_API ILaunchable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Launchable")
	UPrimitiveComponent* GetPrimitiveComponentForLaunch() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Launchable")
	bool CanLaunch() const;

};
