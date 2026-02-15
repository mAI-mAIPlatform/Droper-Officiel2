// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FractureEffect.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UFractureEffect : public UActorComponent
{
	GENERATED_BODY()
public:
	UFractureEffect();
	UFUNCTION(BlueprintCallable) void ApplyFracture(FName LimbBone);
	UFUNCTION(BlueprintCallable) void Splint(FName LimbBone, float HealTime);
	UFUNCTION(BlueprintPure) bool HasFracture(FName LimbBone) const;
	UFUNCTION(BlueprintPure) float GetSpeedPenalty() const;
	UFUNCTION(BlueprintPure) float GetSwayPenalty() const;
protected:
	TSet<FName> FracturedBones;
	UPROPERTY(EditAnywhere) float SpeedPenaltyPerFracture = 0.15f;
	UPROPERTY(EditAnywhere) float SwayPenaltyPerFracture = 0.25f;
};
