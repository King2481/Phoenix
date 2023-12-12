// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "TargetingTypes.generated.h"

class UHealthComponent;
class UPhoenixAbilitySystemComponent;
class UTargetingComponent;
class ITargetable;
class UInteractionData;

USTRUCT(BlueprintType)
struct FTargetableInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UPhoenixAbilitySystemComponent> ABSComponent;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UTargetingComponent> TargetingComponent;

	UPROPERTY(BlueprintReadWrite)
	FText TargetName;

	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<UInteractionData>> PossibleInteractions;

	FTargetableInfo()
	{
		HealthComponent = nullptr;
		ABSComponent = nullptr;
		TargetingComponent = nullptr;
		TargetName = FText::GetEmpty();
	}

	FTargetableInfo(UHealthComponent* InHealthComponent, UPhoenixAbilitySystemComponent* InABSComponent, UTargetingComponent* InTargetingComponent, const FText& InText)
	{
		HealthComponent = InHealthComponent;
		ABSComponent = InABSComponent;
		TargetingComponent = InTargetingComponent;
		TargetName = InText;
	}

	void AddInteractions(TArray<UInteractionData*> InArray)
	{
		PossibleInteractions.Append(InArray);
	}
};

USTRUCT(BlueprintType)
struct FMeshHighlightInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UMeshComponent> MeshToHighlight;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UMaterialInterface> MaterialToUse;

	FMeshHighlightInfo()
	{
		MeshToHighlight = nullptr;
		MaterialToUse = nullptr;
	}

	FMeshHighlightInfo(UMeshComponent* InMeshComponent, UMaterialInterface* InMaterialToUse)
	{
		MeshToHighlight = InMeshComponent;
		MaterialToUse = InMaterialToUse;
	}
};