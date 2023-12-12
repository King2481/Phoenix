// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DamageCalculationType.generated.h"

struct FDiceRollInfo;

/**
 * 
 */
UCLASS(Abstract, Blueprintable, EditInlineNew)
class PHOENIX_API UDamageCalculationTypeBase : public UObject
{
	GENERATED_BODY()

public:

	virtual int32 CalculateDamage() const { return -1; }

};

UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Dice Roll"))
class UDamageCalculationTypeDice : public UDamageCalculationTypeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<FDiceRollInfo> DiceDamage;

	virtual int32 CalculateDamage() const override;
};

UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Range"))
class UDamageCalculationTypeRange : public UDamageCalculationTypeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 Min = 0;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 Max = 0;

	virtual int32 CalculateDamage() const override { return FMath::RandRange(Min, Max); }
};

UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Fixed"))
class UDamageCalculationTypeFixed : public UDamageCalculationTypeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 FixedDamage;

	virtual int32 CalculateDamage() const override { return FixedDamage; }
};
