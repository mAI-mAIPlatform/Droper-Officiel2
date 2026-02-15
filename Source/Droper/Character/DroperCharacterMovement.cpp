// Copyright (c) 2026 mCompany. All Rights Reserved.

#include "DroperCharacterMovement.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

UDroperCharacterMovement::UDroperCharacterMovement()
{
	NavAgentProps.bCanCrouch = true;
	bCanWalkOffLedgesWhenCrouching = true;
	SetCrouchedHalfHeight(50.0f);
}

void UDroperCharacterMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsSliding)
	{
		UpdateSlide(DeltaTime);
	}
}

float UDroperCharacterMovement::GetMaxSpeed() const
{
	if (bIsSliding) return CurrentSlideSpeed;
	if (bIsProne) return ProneSpeed / WeightModifier;

	float BaseSpeed = Super::GetMaxSpeed();

	// Weight modifier reduces speed proportionally
	BaseSpeed /= FMath::Max(WeightModifier, 0.5f);

	// Low stamina slows movement
	if (StaminaPercent < 0.2f)
	{
		BaseSpeed *= FMath::Lerp(0.6f, 1.0f, StaminaPercent / 0.2f);
	}

	return BaseSpeed;
}

float UDroperCharacterMovement::GetMaxAcceleration() const
{
	float BaseAccel = Super::GetMaxAcceleration();
	return BaseAccel / FMath::Max(WeightModifier, 0.5f);
}

void UDroperCharacterMovement::SetStaminaPercent(float Percent)
{
	StaminaPercent = FMath::Clamp(Percent, 0.0f, 1.0f);
}

void UDroperCharacterMovement::SetWeightModifier(float Modifier)
{
	WeightModifier = FMath::Max(Modifier, 0.5f);
}

// --------------------------------------------------
// Prone
// --------------------------------------------------

void UDroperCharacterMovement::EnterProne()
{
	if (bIsProne) return;
	bIsProne = true;

	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if (Owner)
	{
		UCapsuleComponent* Capsule = Owner->GetCapsuleComponent();
		if (Capsule)
		{
			OriginalCapsuleHalfHeight = Capsule->GetScaledCapsuleHalfHeight();
			Capsule->SetCapsuleHalfHeight(ProneCapsuleHalfHeight);
		}
	}
}

void UDroperCharacterMovement::ExitProne()
{
	if (!bIsProne) return;

	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if (Owner)
	{
		// Check if there's room to stand
		UCapsuleComponent* Capsule = Owner->GetCapsuleComponent();
		if (Capsule && OriginalCapsuleHalfHeight > 0.0f)
		{
			FVector Location = Owner->GetActorLocation();
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(Owner);

			FHitResult Hit;
			bool bBlocked = GetWorld()->SweepSingleByChannel(
				Hit, Location, Location + FVector(0, 0, 1),
				FQuat::Identity, ECC_Pawn,
				FCollisionShape::MakeCapsule(Capsule->GetScaledCapsuleRadius(), OriginalCapsuleHalfHeight),
				Params
			);

			if (!bBlocked)
			{
				Capsule->SetCapsuleHalfHeight(OriginalCapsuleHalfHeight);
				bIsProne = false;
			}
		}
	}
}

// --------------------------------------------------
// Slide
// --------------------------------------------------

void UDroperCharacterMovement::StartSlide()
{
	if (bIsSliding || bIsProne) return;

	float CurrentSpeed = Velocity.Size();
	if (CurrentSpeed < SlideMinSpeed) return;

	bIsSliding = true;
	CurrentSlideSpeed = FMath::Max(CurrentSpeed, SlideInitialSpeed);

	// Lower capsule
	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if (Owner && Owner->GetCapsuleComponent())
	{
		OriginalCapsuleHalfHeight = Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		Owner->GetCapsuleComponent()->SetCapsuleHalfHeight(ProneCapsuleHalfHeight);
	}
}

void UDroperCharacterMovement::UpdateSlide(float DeltaTime)
{
	CurrentSlideSpeed -= SlideDeceleration * DeltaTime;

	if (CurrentSlideSpeed <= SlideMinSpeed)
	{
		bIsSliding = false;

		ACharacter* Owner = Cast<ACharacter>(GetOwner());
		if (Owner && Owner->GetCapsuleComponent() && OriginalCapsuleHalfHeight > 0.0f)
		{
			Owner->GetCapsuleComponent()->SetCapsuleHalfHeight(GetCrouchedHalfHeight());
			Owner->Crouch();
		}
	}
}
