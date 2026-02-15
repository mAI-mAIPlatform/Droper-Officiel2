// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SpawnDirector.generated.h"

UCLASS()
class DROPER_API USpawnDirector : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& C) override;
	UFUNCTION(BlueprintCallable) void SetDifficulty(float Level);
	UFUNCTION(BlueprintCallable) void SpawnWave(int32 Count, TSubclassOf<APawn> PawnClass);
	UFUNCTION(BlueprintPure) int32 GetAliveAICount() const { return AliveAI; }
	UFUNCTION(BlueprintCallable) void RegisterSpawnPoint(FVector Location);
protected:
	TArray<FVector> SpawnPoints;
	float DifficultyLevel = 1.0f;
	int32 AliveAI = 0;
};
