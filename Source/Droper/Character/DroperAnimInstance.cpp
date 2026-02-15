// Copyright (c) 2026 mCompany. All Rights Reserved.

#include "DroperAnimInstance.h"
#include "Character/DroperCharacterBase.h"
#include "Character/DroperCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UDroperAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	OwnerCharacter = Cast<ADroperCharacterBase>(TryGetPawnOwner());
}

void UDroperAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!OwnerCharacter.IsValid()) return;

	ADroperCharacterBase* Char = OwnerCharacter.Get();
	UCharacterMovementComponent* MoveComp = Char->GetCharacterMovement();

	FVector Velocity = Char->GetVelocity();
	Speed = Velocity.Size2D();
	Direction = CalculateDirection(Velocity, Char->GetActorRotation());
	bIsInAir = MoveComp->IsFalling();
	bIsCrouching = MoveComp->IsCrouching();
	bIsAlive = Char->IsAlive();
	bIsDowned = Char->IsDowned();

	// Aim offset
	FRotator AimRot = Char->GetBaseAimRotation();
	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(AimRot, Char->GetActorRotation());
	AimPitch = FMath::ClampAngle(DeltaRot.Pitch, -90.0f, 90.0f);
	AimYaw = FMath::ClampAngle(DeltaRot.Yaw, -90.0f, 90.0f);

	// Player-specific
	ADroperCharacter* PlayerChar = Cast<ADroperCharacter>(Char);
	if (PlayerChar)
	{
		bIsSprinting = PlayerChar->IsSprinting();
		bIsADS = PlayerChar->IsADS();
	}

	UpdateLocomotionState();
}

void UDroperAnimInstance::UpdateLocomotionState()
{
	if (bIsInAir)
	{
		LocomotionState = ELocomotionState::Falling;
	}
	else if (Speed < 5.0f)
	{
		LocomotionState = bIsCrouching ? ELocomotionState::Crouching : ELocomotionState::Idle;
	}
	else if (bIsSprinting)
	{
		LocomotionState = ELocomotionState::Sprinting;
	}
	else if (bIsCrouching)
	{
		LocomotionState = ELocomotionState::CrouchWalking;
	}
	else if (Speed > 300.0f)
	{
		LocomotionState = ELocomotionState::Jogging;
	}
	else
	{
		LocomotionState = ELocomotionState::Walking;
	}
}
