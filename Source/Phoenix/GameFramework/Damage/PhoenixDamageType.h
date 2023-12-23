// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "GameplayTagContainer.h" // FGameplayTag
#include "PhoenixDamageType.generated.h"

/**
 * 
 */
UCLASS()
class PHOENIX_API UPhoenixDamageType : public UDamageType
{
	GENERATED_BODY()

public:

	UPhoenixDamageType();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Phoenix Damage Type")
	FGameplayTag DamageTypeTag;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Phoenix Damage Type")
	bool bDamageCarriesOverOnHealthDepletion;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Phoenix Damage Type")
	bool bNonLethal;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Phoenix Damage Type")
	bool bIsHeal;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Phoenix Damage Type")
	FLinearColor DamageTypeColor;
};
