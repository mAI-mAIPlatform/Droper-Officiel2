// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "DoorActor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

ADoorActor::ADoorActor()
{
	PrimaryActorTick.bCanEverTick = true; bReplicates = true;
	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Frame")); SetRootComponent(FrameMesh);
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door")); DoorMesh->SetupAttachment(FrameMesh);
}

void ADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (FMath::Abs(CurrentAngle - TargetAngle) > 0.5f)
	{
		CurrentAngle = FMath::FInterpTo(CurrentAngle, TargetAngle, DeltaTime, OpenSpeed);
		DoorMesh->SetRelativeRotation(FRotator(0, CurrentAngle, 0));
	}
	else if (DoorState == EDoorState::Opening) DoorState = EDoorState::Open;
	else if (DoorState == EDoorState::Closing) DoorState = EDoorState::Closed;
}

void ADoorActor::Interact(AActor* Instigator)
{
	if (bIsLocked || DoorState == EDoorState::Breached) return;
	if (DoorState == EDoorState::Closed || DoorState == EDoorState::Closing)
	{
		// Determine open direction based on instigator position
		FVector ToInstigator = Instigator->GetActorLocation() - GetActorLocation();
		float Dot = FVector::DotProduct(ToInstigator, GetActorForwardVector());
		TargetAngle = Dot > 0 ? -OpenAngle : OpenAngle;
		DoorState = EDoorState::Opening;
		if (OpenSFX) UGameplayStatics::PlaySoundAtLocation(this, OpenSFX, GetActorLocation());
	}
	else { TargetAngle = 0.0f; DoorState = EDoorState::Closing; }
}

void ADoorActor::Breach(FVector ImpactPoint, float Force)
{
	DoorState = EDoorState::Breached;
	DoorMesh->SetSimulatePhysics(true);
	FVector Dir = (DoorMesh->GetComponentLocation() - ImpactPoint).GetSafeNormal();
	DoorMesh->AddImpulse(Dir * Force * BreachForce);
	if (BreachSFX) UGameplayStatics::PlaySoundAtLocation(this, BreachSFX, GetActorLocation());
}

void ADoorActor::PeekOpen(float Amount) { TargetAngle = OpenAngle * FMath::Clamp(Amount, 0.0f, 0.3f); }
