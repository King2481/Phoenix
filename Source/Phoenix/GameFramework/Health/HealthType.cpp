// Created by Bruce Crum.


#include "Phoenix/GameFramework/Health/HealthType.h"

UHealthType::UHealthType()
{
	Priority = 0;
	MaxValue = 300;
	bIsCritical = false;
	bAbsorbsLeftoverDamageOnDepletion = false;
}