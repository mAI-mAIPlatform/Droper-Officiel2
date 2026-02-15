// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "GrenadeActor.h"
#include "Kismet/GameplayStatics.h"
AGrenadeActor::AGrenadeActor() { GadgetType = EGadgetType::Grenade; Damage = 150.0f; EffectRadius = 500.0f; }
void AGrenadeActor::Use(AActor* User) { Super::Use(User); GadgetMesh->SetSimulatePhysics(true);
	FVector Dir = User->GetActorForwardVector() + FVector(0,0,0.3f); GadgetMesh->AddImpulse(Dir * 1500.0f);
	GetWorldTimerManager().SetTimer(FuseTimer, this, &AGrenadeActor::Detonate, FuseTime, false);
}
void AGrenadeActor::Detonate()
{
	UGameplayStatics::ApplyRadialDamage(this, Damage, GetActorLocation(), EffectRadius, nullptr, {}, this, GetInstigatorController());
	Destroy();
}
