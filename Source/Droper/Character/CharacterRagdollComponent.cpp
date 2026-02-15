// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "CharacterRagdollComponent.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

UCharacterRagdollComponent::UCharacterRagdollComponent() { PrimaryComponentTick.bCanEverTick = false; }

void UCharacterRagdollComponent::ActivateRagdoll(FVector Impulse, FName BoneName)
{
	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if (!Owner) return;
	bIsRagdoll = true;
	Owner->GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	Owner->GetMesh()->SetSimulatePhysics(true);
	Owner->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Owner->GetCharacterMovement()->DisableMovement();
	if (!Impulse.IsNearlyZero() && !BoneName.IsNone())
	{
		Owner->GetMesh()->AddImpulse(Impulse * ImpulseMultiplier, BoneName, true);
	}
}

void UCharacterRagdollComponent::DeactivateRagdoll()
{
	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if (!Owner) return;
	bIsRagdoll = false;
	Owner->GetMesh()->SetSimulatePhysics(false);
	Owner->GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));
	Owner->GetMesh()->AttachToComponent(Owner->GetCapsuleComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Owner->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void UCharacterRagdollComponent::BlendToRagdoll(float BlendTime)
{
	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if (!Owner) return;
	Owner->GetMesh()->SetPhysicsBlendWeight(0.0f);
	ActivateRagdoll();
	// Blend weight would be interpolated over BlendTime in tick — simplified here
	Owner->GetMesh()->SetPhysicsBlendWeight(1.0f);
}
