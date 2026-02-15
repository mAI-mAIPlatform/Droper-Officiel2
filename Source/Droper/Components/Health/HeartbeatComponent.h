// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HeartbeatComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UHeartbeatComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UHeartbeatComponent();
	virtual void TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F) override;
	UFUNCTION(BlueprintPure) float GetBPM() const { return CurrentBPM; }
	UFUNCTION(BlueprintPure) float GetNormalizedBPM() const { return (CurrentBPM - RestingBPM) / (MaxBPM - RestingBPM); }
	void SetStaminaFactor(float Factor);
	void SetDamageFactor(float Factor);
	void SetAdrenalineFactor(float Factor);
protected:
	UPROPERTY(EditAnywhere) float RestingBPM = 70.0f;
	UPROPERTY(EditAnywhere) float MaxBPM = 180.0f;
	UPROPERTY(EditAnywhere) float RecoveryRate = 5.0f;
	float CurrentBPM = 70.0f;
	float StaminaFactor = 0.0f, DamageFactor = 0.0f, AdrenalineFactor = 0.0f;
};
