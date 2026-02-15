// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BallisticsSubsystem.generated.h"

UCLASS()
class DROPER_API UBallisticsSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	UFUNCTION(BlueprintPure) FVector GetWindVector() const { return WindVector; }
	UFUNCTION(BlueprintCallable) void SetWindVector(FVector Wind) { WindVector = Wind; }
	UFUNCTION(BlueprintPure) float GetAirDensity() const { return AirDensity; }
	UFUNCTION(BlueprintCallable) FVector ApplyWindToVelocity(FVector Velocity, float DeltaTime) const;
	UFUNCTION(BlueprintPure) float CalculateBulletDrop(float Distance, float MuzzleVelocity) const;
protected:
	FVector WindVector = FVector::ZeroVector;
	float AirDensity = 1.225f; // kg/m³ at sea level
};
