// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CoverSystem.generated.h"

USTRUCT(BlueprintType) struct FCoverPoint { GENERATED_BODY()
	UPROPERTY(EditAnywhere) FVector Location; UPROPERTY(EditAnywhere) FVector Normal;
	UPROPERTY(EditAnywhere) bool bIsCrouch = false; UPROPERTY(EditAnywhere) bool bIsOccupied = false;
};

UCLASS()
class DROPER_API UCoverSystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	UFUNCTION(BlueprintCallable) void RegisterCoverPoint(const FCoverPoint& Point);
	UFUNCTION(BlueprintPure) FCoverPoint FindBestCover(FVector From, FVector ThreatLocation, float MaxDistance) const;
	UFUNCTION(BlueprintCallable) void OccupyCover(int32 Index);
	UFUNCTION(BlueprintCallable) void ReleaseCover(int32 Index);
protected:
	TArray<FCoverPoint> CoverPoints;
};
