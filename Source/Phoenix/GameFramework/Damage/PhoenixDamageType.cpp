// Created by Bruce Crum.


#include "Phoenix/GameFramework/Damage/PhoenixDamageType.h"

UPhoenixDamageType::UPhoenixDamageType()
{
	bDamageCarriesOverOnHealthDepletion = true;
	bNonLethal = false;
	bIsHeal = false;
	DamageTypeColor = FLinearColor::White;
}