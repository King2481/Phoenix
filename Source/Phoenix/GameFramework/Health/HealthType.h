// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HealthType.generated.h"

/**
 * 
 */
UCLASS()
class PHOENIX_API UHealthType : public UDataAsset
{
	GENERATED_BODY()

public:

	UHealthType();
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Health Type")
	uint8 Priority;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Health Type")
	int32 MaxValue;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Health Type")
	bool bIsCritical;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Health Type")
	bool bAbsorbsLeftoverDamageOnDepletion;
};
