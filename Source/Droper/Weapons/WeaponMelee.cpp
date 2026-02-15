// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "WeaponMelee.h"
AWeaponMelee::AWeaponMelee()
{
	WeaponStats.Category = EWeaponCategory::Melee;
	WeaponStats.FireRate = 60.0f; WeaponStats.BaseDamage = 50.0f;
	WeaponStats.AvailableFireModes = { EFireMode::Semi };
}
void AWeaponMelee::StartFire()
{
	AController* C = GetInstigatorController();
	if (!C) return;
	FVector Start; FRotator Rot; C->GetPlayerViewPoint(Start, Rot);
	TArray<FHitResult> Hits;
	FCollisionQueryParams Params; Params.AddIgnoredActor(this); Params.AddIgnoredActor(GetOwner());
	GetWorld()->SweepMultiByChannel(Hits, Start, Start + Rot.Vector() * MeleeRange, FQuat::Identity, ECC_Pawn, FCollisionShape::MakeSphere(30.0f), Params);
	for (const FHitResult& Hit : Hits) { ProcessHit(Hit); }
	OnWeaponFired.Broadcast();
}
