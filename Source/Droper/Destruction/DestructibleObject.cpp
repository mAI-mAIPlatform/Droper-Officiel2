// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "DestructibleObject.h"
#include "Components/StaticMeshComponent.h"
ADestructibleObject::ADestructibleObject() { MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); SetRootComponent(MeshComp); bReplicates = true; }
void ADestructibleObject::ApplyDamage(float D, FVector IP, FVector IN) {
	CurrentHealth -= D;
	if (CurrentHealth <= 0) { if (DestroyedMesh) MeshComp->SetStaticMesh(DestroyedMesh); MeshComp->SetSimulatePhysics(true); OnDestructionComplete.Broadcast(); }
}
float ADestructibleObject::GetHealthPercent() const { return MaxHealth > 0 ? CurrentHealth / MaxHealth : 0; }
