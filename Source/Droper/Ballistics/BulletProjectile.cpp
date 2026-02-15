// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "BulletProjectile.h"
ABulletProjectile::ABulletProjectile() { Damage = 30.0f; DragCoefficient = 0.0005f; }
void ABulletProjectile::OnImpact(const FHitResult& Hit)
{
	float Angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(-GetVelocity().GetSafeNormal(), Hit.ImpactNormal)));
	if (Angle < RicochetAngleThreshold && PenetrationPower > 0.5f)
	{
		// Ricochet
		FVector Reflected = FMath::GetReflectionVector(GetVelocity(), Hit.ImpactNormal);
		SetActorLocation(Hit.ImpactPoint + Hit.ImpactNormal * 2.0f);
		if (ProjectileMovement) ProjectileMovement->Velocity = Reflected * 0.5f;
		PenetrationPower *= 0.3f; Damage *= 0.3f;
		return;
	}
	// Apply damage
	if (Hit.GetActor()) { /* Damage application through subsystem */ }
	Super::OnImpact(Hit);
}
