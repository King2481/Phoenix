// Created by Bruce Crum.


#include "Phoenix/Characters/CharacterInfo.h"

UCharacterInfo::UCharacterInfo()
{
	CharacterName = FText::GetEmpty();
	Species = nullptr;
	EquipmentSlotLayout = nullptr;
	CharacterClass = nullptr;
	Faction = nullptr;
}