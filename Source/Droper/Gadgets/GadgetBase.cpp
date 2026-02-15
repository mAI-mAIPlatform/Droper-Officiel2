// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "GadgetBase.h"
#include "Components/StaticMeshComponent.h"
AGadgetBase::AGadgetBase()
{
	bReplicates = true; PrimaryActorTick.bCanEverTick = true;
	GadgetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(GadgetMesh);
}
void AGadgetBase::Use(AActor* User) { if (CurrentCharges > 0) CurrentCharges--; }
void AGadgetBase::Detonate() {}
