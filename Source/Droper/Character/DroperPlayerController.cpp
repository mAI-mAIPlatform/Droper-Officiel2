// Copyright (c) 2026 mCompany. All Rights Reserved.

#include "DroperPlayerController.h"
#include "Character/DroperCharacter.h"
#include "Interaction/InteractableInterface.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h"

ADroperPlayerController::ADroperPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADroperPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ADroperPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ADroperPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ADroperPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsLocalController())
	{
		PerformInteractionTrace();
	}
}

ADroperCharacter* ADroperPlayerController::GetDroperCharacter() const
{
	return Cast<ADroperCharacter>(GetPawn());
}

void ADroperPlayerController::TogglePauseMenu()
{
	bIsPaused = !bIsPaused;

	if (bIsPaused)
	{
		SetInputMode(FInputModeGameAndUI());
		bShowMouseCursor = true;
	}
	else
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}

void ADroperPlayerController::TransitionToSpectator()
{
	ChangeState(NAME_Spectating);
}

void ADroperPlayerController::ShowDeathScreen(AController* Killer)
{
	// Trigger HUD death screen widget
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}

void ADroperPlayerController::PerformInteractionTrace()
{
	ADroperCharacter* DroperChar = GetDroperCharacter();
	if (!DroperChar) return;

	FVector TraceStart;
	FRotator TraceRot;
	GetPlayerViewPoint(TraceStart, TraceRot);

	FVector TraceEnd = TraceStart + TraceRot.Vector() * InteractionTraceDistance;

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(DroperChar);
	QueryParams.bTraceComplex = false;

	bool bHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		TraceStart,
		TraceEnd,
		FQuat::Identity,
		ECC_Visibility,
		FCollisionShape::MakeSphere(InteractionTraceRadius),
		QueryParams
	);

	if (bHit && HitResult.GetActor())
	{
		if (HitResult.GetActor()->Implements<UInteractable>())
		{
			CurrentInteractionTarget = HitResult.GetActor();
			return;
		}
	}

	CurrentInteractionTarget = nullptr;
}
