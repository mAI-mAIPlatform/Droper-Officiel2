// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "ItemBase.h"
#include "Components/StaticMeshComponent.h"
AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComp);
	MeshComp->SetCollisionProfileName(TEXT("PhysicsActor"));
	MeshComp->SetSimulatePhysics(true);
}
