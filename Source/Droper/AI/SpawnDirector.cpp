// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "SpawnDirector.h"
#include "Kismet/GameplayStatics.h"
void USpawnDirector::Initialize(FSubsystemCollectionBase& C) { Super::Initialize(C); }
void USpawnDirector::SetDifficulty(float L) { DifficultyLevel = FMath::Clamp(L, 0.5f, 3.0f); }
void USpawnDirector::SpawnWave(int32 Count, TSubclassOf<APawn> PawnClass)
{
	UWorld* W = GetWorld(); if (!W || SpawnPoints.Num() == 0) return;
	for (int32 i = 0; i < Count; i++)
	{
		FVector Loc = SpawnPoints[FMath::RandRange(0, SpawnPoints.Num()-1)];
		FActorSpawnParameters Params; Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		if (W->SpawnActor<APawn>(PawnClass, &Loc, nullptr, Params)) AliveAI++;
	}
}
void USpawnDirector::RegisterSpawnPoint(FVector L) { SpawnPoints.Add(L); }
