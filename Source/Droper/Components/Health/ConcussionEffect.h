// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ConcussionEffect.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UConcussionEffect : public UActorComponent
{
	GENERATED_BODY()
public:
	UConcussionEffect();
	virtual void TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F) override;
	UFUNCTION(BlueprintCallable) void ApplyConcussion(float Severity);
	UFUNCTION(BlueprintPure) bool IsConcussed() const { return ConcussionTimer > 0.0f; }
	UFUNCTION(BlueprintPure) float GetBlurIntensity() const;
	UFUNCTION(BlueprintPure) float GetInputDelay() const;
	UFUNCTION(BlueprintPure) float GetTinnitusVolume() const;
protected:
	float ConcussionTimer = 0.0f;
	float ConcussionSeverity = 0.0f;
	UPROPERTY(EditAnywhere) float MaxConcussionDuration = 8.0f;
	UPROPERTY(EditAnywhere) float MaxBlur = 3.0f;
	UPROPERTY(EditAnywhere) float MaxInputDelay = 0.15f;
};
