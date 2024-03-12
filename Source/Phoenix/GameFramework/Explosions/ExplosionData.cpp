// Created by Bruce Crum.


#include "Phoenix/GameFramework/Explosions/ExplosionData.h"

UExplosionData::UExplosionData()
{
	ExplosionInnerRadius = 150.0f;
	ExplosionOuterRadius = 450.0f;
	ExplosionInnerDamage = 100;
	ExplosionOuterDamage = 10;
	DamageFalloffCurve.GetRichCurve()->AddKey(0.0f, 0.0f);
	DamageFalloffCurve.GetRichCurve()->AddKey(1.0f, 1.0f);
	ExplosionDamageTypeClass = nullptr;

	CameraShakeData = FCameraShakeData();

	ExplosionSound = nullptr;
	ExplosionFX = nullptr;

	ExplosionInnerForceImpulseRadius = 150.0f;
	ExplosionOuterForceImpulseRadius = 450.0f;
	ExplosionInnerForceImpulseStrength = 100.0f;
	ExplosionOuterForceImpulseStrength = 10.0f;
	ImpulseFalloffCurve.GetRichCurve()->AddKey(0.0f, 0.0f);
	ImpulseFalloffCurve.GetRichCurve()->AddKey(1.0f, 1.0f);
}