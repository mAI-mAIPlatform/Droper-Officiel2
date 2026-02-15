// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "ArmorComponent.h"

UArmorComponent::UArmorComponent() { PrimaryComponentTick.bCanEverTick = false; }

float UArmorComponent::ProcessDamage(float IncomingDamage, float ArmorPierce, FVector HitDirection)
{
	EArmorZone HitZone = DetermineHitZone(HitDirection);
	for (FArmorPlate& Plate : Plates)
	{
		if (Plate.Zone == HitZone && !Plate.IsDestroyed())
		{
			float EffectiveReduction = Plate.DamageReduction * (1.0f - ArmorPierce);
			float Absorbed = IncomingDamage * EffectiveReduction;
			Plate.CurrentDurability -= Absorbed;
			if (Plate.CurrentDurability <= 0.0f) { Plate.CurrentDurability = 0.0f; OnArmorDestroyed.Broadcast(HitZone); }
			else { OnArmorDamaged.Broadcast(HitZone, Plate.CurrentDurability); }
			return IncomingDamage - Absorbed;
		}
	}
	return IncomingDamage; // No armor in that zone
}

void UArmorComponent::RepairArmor(EArmorZone Zone, float Amount)
{
	for (FArmorPlate& Plate : Plates)
	{
		if (Plate.Zone == Zone) { Plate.CurrentDurability = FMath::Min(Plate.MaxDurability, Plate.CurrentDurability + Amount); return; }
	}
}

float UArmorComponent::GetArmorDurability(EArmorZone Zone) const
{
	for (const FArmorPlate& Plate : Plates) { if (Plate.Zone == Zone) return Plate.GetDurabilityPercent(); }
	return 0.0f;
}

EArmorZone UArmorComponent::DetermineHitZone(FVector HitDirection) const
{
	FVector Forward = GetOwner()->GetActorForwardVector();
	FVector Right = GetOwner()->GetActorRightVector();
	float ForwardDot = FVector::DotProduct(HitDirection.GetSafeNormal(), Forward);
	float RightDot = FVector::DotProduct(HitDirection.GetSafeNormal(), Right);
	if (FMath::Abs(ForwardDot) > FMath::Abs(RightDot))
		return ForwardDot > 0 ? EArmorZone::Front : EArmorZone::Back;
	else
		return RightDot > 0 ? EArmorZone::RightSide : EArmorZone::LeftSide;
}
