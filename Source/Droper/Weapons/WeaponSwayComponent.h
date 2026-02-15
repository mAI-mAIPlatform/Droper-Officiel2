// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponSwayComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UWeaponSwayComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UWeaponSwayComponent();
	virtual void TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F) override;
	UFUNCTION(BlueprintPure) FVector2D GetSwayOffset() const { return SwayOffset; }
	void SetHeartbeatFactor(float BPMNormalized);
	void SetStaminaFactor(float Factor);
	void SetBreathHold(bool bHolding);
protected:
	FVector2D SwayOffset = FVector2D::ZeroVector;
	UPROPERTY(EditAnywhere) float BaseSwayAmplitude = 0.5f;
	UPROPERTY(EditAnywhere) float BaseSwayFrequency = 1.5f;
	UPROPERTY(EditAnywhere) float ADSSwayReduction = 0.3f;
	float HeartbeatMod = 0.0f, StaminaMod = 0.0f;
	bool bHoldingBreath = false;
	float SwayTime = 0.0f;
};
