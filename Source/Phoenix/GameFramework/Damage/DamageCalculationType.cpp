// Created by Bruce Crum.


#include "Phoenix/GameFramework/Damage/DamageCalculationType.h"
#include "Phoenix/GameFramework/PhoenixGameplayStatics.h"

int32 UDamageCalculationTypeDice::CalculateDamage() const
{
	return UPhoenixGameplayStatics::RollDice(DiceDamage);
}