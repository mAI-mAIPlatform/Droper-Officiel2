// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "ExplosiveProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

AExplosiveProjectile::AExplosiveProjectile() { GravityScale = 1.5f; DragCoefficient = 0.002f; }
void AExplosiveProjectile::OnImpact(const FHitResult& Hit) { Explode(); }
void AExplosiveProjectile::Explode()
{
	UGameplayStatics::ApplyRadialDamage(this, ExplosionDamage, GetActorLocation(), ExplosionRadius, nullptr, {}, this, GetInstigatorController());
	if (ExplosionVFX) UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionVFX, GetActorLocation());
	if (ExplosionSFX) UGameplayStatics::PlaySoundAtLocation(this, ExplosionSFX, GetActorLocation());
	Destroy();
}
