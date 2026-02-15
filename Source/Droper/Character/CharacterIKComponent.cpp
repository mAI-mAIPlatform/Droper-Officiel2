// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "CharacterIKComponent.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

UCharacterIKComponent::UCharacterIKComponent() { PrimaryComponentTick.bCanEverTick = true; }

void UCharacterIKComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateFootIK(DeltaTime);
	UpdateHandIK();
}

void UCharacterIKComponent::UpdateFootIK(float DeltaTime)
{
	FVector LeftTarget = TraceFootPosition(FName("foot_l"));
	FVector RightTarget = TraceFootPosition(FName("foot_r"));
	LeftFootOffset = FMath::VInterpTo(LeftFootOffset, LeftTarget, DeltaTime, FootInterpSpeed);
	RightFootOffset = FMath::VInterpTo(RightFootOffset, RightTarget, DeltaTime, FootInterpSpeed);
}

void UCharacterIKComponent::UpdateHandIK()
{
	// Left hand grip driven by weapon socket — placeholder
}

FVector UCharacterIKComponent::TraceFootPosition(FName SocketName) const
{
	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if (!Owner || !Owner->GetMesh()) return FVector::ZeroVector;

	FVector SocketLoc = Owner->GetMesh()->GetSocketLocation(SocketName);
	FVector Start = SocketLoc + FVector(0, 0, FootTraceDistance);
	FVector End = SocketLoc - FVector(0, 0, FootTraceDistance);

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Owner);

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		return FVector(0, 0, (Hit.ImpactPoint - SocketLoc).Z);
	}
	return FVector::ZeroVector;
}
