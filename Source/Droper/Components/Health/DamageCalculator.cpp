// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "DamageCalculator.h"

float UDamageCalculator::CalculatePenetration(float BaseDamage, float ArmorClass, float ArmorPierce, float Angle)
{
	float AngleMod = FMath::Clamp(FMath::Cos(FMath::DegreesToRadians(Angle)), 0.1f, 1.0f);
	float ArmorFactor = FMath::Clamp(1.0f - (ArmorClass * 0.1f * (1.0f - ArmorPierce)), 0.0f, 1.0f);
	return BaseDamage * ArmorFactor * AngleMod;
}

float UDamageCalculator::CalculateDistanceFalloff(float BaseDamage, float Distance, float EffectiveRange, float MaxRange)
{
	if (Distance <= EffectiveRange) return BaseDamage;
	if (Distance >= MaxRange) return BaseDamage * 0.1f;
	float Alpha = (Distance - EffectiveRange) / (MaxRange - EffectiveRange);
	return FMath::Lerp(BaseDamage, BaseDamage * 0.1f, Alpha * Alpha);
}

float UDamageCalculator::GetBodyPartMultiplier(EBodyPart Part)
{
	switch (Part)
	{
		case EBodyPart::Head: return 4.0f;
		case EBodyPart::Neck: return 3.5f;
		case EBodyPart::UpperTorso: return 1.0f;
		case EBodyPart::LowerTorso: return 0.9f;
		case EBodyPart::LeftArm: case EBodyPart::RightArm: return 0.6f;
		case EBodyPart::LeftLeg: case EBodyPart::RightLeg: return 0.7f;
		default: return 1.0f;
	}
}

float UDamageCalculator::CalculateFinalDamage(float BaseDamage, EBodyPart Part, float Distance, float EffectiveRange, float MaxRange, float ArmorClass, float ArmorPierce, float HitAngle)
{
	float Damage = BaseDamage * GetBodyPartMultiplier(Part);
	Damage = CalculateDistanceFalloff(Damage, Distance, EffectiveRange, MaxRange);
	Damage = CalculatePenetration(Damage, ArmorClass, ArmorPierce, HitAngle);
	return FMath::Max(0.0f, Damage);
}

float UDamageCalculator::GetHemorrhageChance(EBodyPart Part, float DamagePercent)
{
	switch (Part)
	{
		case EBodyPart::Neck: return DamagePercent * 0.8f;
		case EBodyPart::LeftArm: case EBodyPart::RightArm: case EBodyPart::LeftLeg: case EBodyPart::RightLeg: return DamagePercent * 0.5f;
		case EBodyPart::UpperTorso: case EBodyPart::LowerTorso: return DamagePercent * 0.4f;
		default: return DamagePercent * 0.2f;
	}
}

float UDamageCalculator::GetFractureChance(EBodyPart Part, float DamagePercent)
{
	switch (Part)
	{
		case EBodyPart::LeftArm: case EBodyPart::RightArm: case EBodyPart::LeftLeg: case EBodyPart::RightLeg: return DamagePercent * 0.6f;
		default: return DamagePercent * 0.15f;
	}
}
