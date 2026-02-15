// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Types/DamageTypes.h"
#include "DamageCalculator.generated.h"

UCLASS(BlueprintType)
class DROPER_API UDamageCalculator : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category="Droper|Damage")
	static float CalculatePenetration(float BaseDamage, float ArmorClass, float ArmorPierce, float Angle);

	UFUNCTION(BlueprintPure, Category="Droper|Damage")
	static float CalculateDistanceFalloff(float BaseDamage, float Distance, float EffectiveRange, float MaxRange);

	UFUNCTION(BlueprintPure, Category="Droper|Damage")
	static float GetBodyPartMultiplier(EBodyPart Part);

	UFUNCTION(BlueprintPure, Category="Droper|Damage")
	static float CalculateFinalDamage(float BaseDamage, EBodyPart Part, float Distance, float EffectiveRange, float MaxRange, float ArmorClass, float ArmorPierce, float HitAngle);

	UFUNCTION(BlueprintPure, Category="Droper|Damage")
	static float GetHemorrhageChance(EBodyPart Part, float DamagePercent);

	UFUNCTION(BlueprintPure, Category="Droper|Damage")
	static float GetFractureChance(EBodyPart Part, float DamagePercent);
};
