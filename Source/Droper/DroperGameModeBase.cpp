// Copyright (c) 2026 mCompany. All Rights Reserved.

#include "DroperGameModeBase.h"
#include "Droper.h"
#include "Character/DroperPlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "EngineUtils.h"
#include "TimerManager.h"

ADroperGameModeBase::ADroperGameModeBase()
{
	bUseSeamlessTravel = true;
}

void ADroperGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	UE_LOG(LogDroper, Log, TEXT("InitGame: Map=%s"), *MapName);
}

void ADroperGameModeBase::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	if (ConnectedPlayers.Num() >= MaxPlayers)
	{
		ErrorMessage = TEXT("Server is full");
		return;
	}

	if (CurrentMatchPhase == EDroperMatchPhase::PostMatch || CurrentMatchPhase == EDroperMatchPhase::TravellingToMap)
	{
		ErrorMessage = TEXT("Match is ending");
		return;
	}

	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

void ADroperGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ConnectedPlayers.AddUnique(NewPlayer);
	AssignTeam(NewPlayer);
	OnPlayerJoined.Broadcast(NewPlayer);

	UE_LOG(LogDroper, Log, TEXT("Player joined: %s (%d/%d)"),
		*NewPlayer->GetName(), ConnectedPlayers.Num(), MaxPlayers);
}

void ADroperGameModeBase::Logout(AController* Exiting)
{
	APlayerController* PC = Cast<APlayerController>(Exiting);
	if (PC)
	{
		ConnectedPlayers.Remove(PC);
		OnPlayerLeft.Broadcast(PC);
	}

	Super::Logout(Exiting);
}

void ADroperGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	// Subclasses override for mode-specific spawn logic
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
}

// --------------------------------------------------
// Match Flow
// --------------------------------------------------

void ADroperGameModeBase::SetMatchPhase(EDroperMatchPhase NewPhase)
{
	if (CurrentMatchPhase == NewPhase) return;

	EDroperMatchPhase OldPhase = CurrentMatchPhase;
	CurrentMatchPhase = NewPhase;

	UE_LOG(LogDroper, Log, TEXT("Match phase changed: %d -> %d"), (int32)OldPhase, (int32)NewPhase);
	OnMatchPhaseChanged.Broadcast(NewPhase);
}

void ADroperGameModeBase::StartWarmup()
{
	SetMatchPhase(EDroperMatchPhase::Warmup);

	GetWorldTimerManager().SetTimer(
		WarmupTimerHandle,
		this,
		&ADroperGameModeBase::OnWarmupEnd,
		WarmupDuration,
		false
	);
}

void ADroperGameModeBase::StartMatch_Droper()
{
	SetMatchPhase(EDroperMatchPhase::Active);

	if (MatchDuration > 0.0f)
	{
		GetWorldTimerManager().SetTimer(
			MatchTimerHandle,
			this,
			&ADroperGameModeBase::OnMatchTimeExpired,
			MatchDuration,
			false
		);
	}
}

void ADroperGameModeBase::EndMatch(const FString& Reason)
{
	GetWorldTimerManager().ClearTimer(MatchTimerHandle);
	SetMatchPhase(EDroperMatchPhase::PostMatch);

	UE_LOG(LogDroper, Log, TEXT("Match ended: %s"), *Reason);
}

void ADroperGameModeBase::OnWarmupEnd()
{
	StartMatch_Droper();
}

void ADroperGameModeBase::OnMatchTimeExpired()
{
	EndMatch(TEXT("Time expired"));
}

// --------------------------------------------------
// Spawn & Team
// --------------------------------------------------

AActor* ADroperGameModeBase::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	// Default: find a random unoccupied PlayerStart
	TArray<APlayerStart*> PlayerStarts;
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		PlayerStarts.Add(*It);
	}

	if (PlayerStarts.Num() > 0)
	{
		return PlayerStarts[FMath::RandRange(0, PlayerStarts.Num() - 1)];
	}

	return Super::FindPlayerStart_Implementation(Player, IncomingName);
}

UClass* ADroperGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

int32 ADroperGameModeBase::AssignTeam(APlayerController* Player)
{
	// Simple round-robin team assignment — subclasses can override
	static int32 TeamCounter = 0;
	int32 AssignedTeam = TeamCounter % MaxTeams;
	TeamCounter++;
	return AssignedTeam;
}
