// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "AnimNotify_Footstep.h"
#include "Components/SkeletalMeshComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
void UAnimNotify_Footstep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Anim, const FAnimNotifyEventReference& Ref)
{
	if (!MeshComp) return;
	FVector FootLoc = MeshComp->GetSocketLocation(FootBone);
	FHitResult Hit;
	if (MeshComp->GetWorld()->LineTraceSingleByChannel(Hit, FootLoc, FootLoc - FVector(0,0,50), ECC_Visibility))
	{
		// Surface type from physical material — play appropriate sound
	}
}
