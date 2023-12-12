// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterInfo.generated.h"

class APhoenixCharacter;
class USpeciesType;
class UEquipmentSlotLayout;
class UFactionInfo;

/**
 * 
 */
UCLASS()
class PHOENIX_API UCharacterInfo : public UDataAsset
{
	GENERATED_BODY()

public:

	UCharacterInfo();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Character Info")
	FText CharacterName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Character Info")
	TSubclassOf<APhoenixCharacter> CharacterClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Character Info")
	TObjectPtr<USpeciesType> Species;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Character Info")
	TObjectPtr<UEquipmentSlotLayout> EquipmentSlotLayout;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Character Info")
	TObjectPtr<UFactionInfo> Faction;
	
};
