// Copyright (c) 2026 mCompany. All Rights Reserved.

#include "DroperSpectatorPawn.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

ADroperSpectatorPawn::ADroperSpectatorPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADroperSpectatorPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ADroperSpectatorPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentMode == ESpectatorMode::FollowPlayer)
	{
		UpdateFollowCamera(DeltaTime);
	}
}

void ADroperSpectatorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Enhanced Input bindings would be added here for spectator-specific controls
}

void ADroperSpectatorPawn::SetSpectatorMode(ESpectatorMode NewMode)
{
	CurrentMode = NewMode;

	if (NewMode == ESpectatorMode::FollowPlayer)
	{
		TArray<AActor*> Targets = GetSpectateTargets();
		if (Targets.Num() > 0)
		{
			FollowTargetIndex = FMath::Clamp(FollowTargetIndex, 0, Targets.Num() - 1);
			FollowTarget = Targets[FollowTargetIndex];
		}
	}
	else
	{
		FollowTarget = nullptr;
	}
}

void ADroperSpectatorPawn::FollowNextPlayer()
{
	TArray<AActor*> Targets = GetSpectateTargets();
	if (Targets.Num() == 0) return;

	FollowTargetIndex = (FollowTargetIndex + 1) % Targets.Num();
	FollowTarget = Targets[FollowTargetIndex];
}

void ADroperSpectatorPawn::FollowPreviousPlayer()
{
	TArray<AActor*> Targets = GetSpectateTargets();
	if (Targets.Num() == 0) return;

	FollowTargetIndex = (FollowTargetIndex - 1 + Targets.Num()) % Targets.Num();
	FollowTarget = Targets[FollowTargetIndex];
}

void ADroperSpectatorPawn::UpdateFollowCamera(float DeltaTime)
{
	if (!FollowTarget) return;

	const FVector TargetLocation = FollowTarget->GetActorLocation() + 
		FollowTarget->GetActorRotation().RotateVector(FollowCamOffset);
	const FRotator TargetRotation = (FollowTarget->GetActorLocation() - TargetLocation).Rotation();

	SetActorLocation(FMath::VInterpTo(GetActorLocation(), TargetLocation, DeltaTime, FollowCamInterpSpeed));
	
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PC->SetControlRotation(FMath::RInterpTo(PC->GetControlRotation(), TargetRotation, DeltaTime, FollowCamInterpSpeed));
	}
}

TArray<AActor*> ADroperSpectatorPawn::GetSpectateTargets() const
{
	TArray<AActor*> Targets;
	
	UWorld* World = GetWorld();
	if (!World) return Targets;

	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC && PC->GetPawn() && PC != GetController())
		{
			Targets.Add(PC->GetPawn());
		}
	}

	return Targets;
}
