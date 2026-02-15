// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "ImpactEffectManager.h"
#include "Kismet/GameplayStatics.h"
void UImpactEffectManager::SpawnImpactEffect(UWorld* World, const FHitResult& Hit, ESurfaceResponse Surface)
{
	if (!World) return;
	// Spawn decal + particles based on surface type — placeholder
	UGameplayStatics::SpawnDecalAtLocation(World, nullptr, FVector(5), Hit.ImpactPoint, Hit.ImpactNormal.Rotation(), 30.0f);
}
