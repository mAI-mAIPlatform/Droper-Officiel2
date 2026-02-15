// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BodyCamComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UBodyCamComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UBodyCamComponent();
	virtual void TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F) override;
	UFUNCTION(BlueprintCallable) void SetBodyCamEnabled(bool bEnabled);
	UFUNCTION(BlueprintPure) bool IsBodyCamEnabled() const { return bBodyCamActive; }
	UFUNCTION(BlueprintPure) float GetCurrentFisheyeStrength() const { return FisheyeStrength; }
	UFUNCTION(BlueprintPure) float GetCurrentGrainIntensity() const { return GrainIntensity; }
	UFUNCTION(BlueprintPure) float GetCurrentVignetteIntensity() const { return VignetteIntensity; }
protected:
	bool bBodyCamActive = true;
	UPROPERTY(EditAnywhere) float FisheyeStrength = 0.3f;
	UPROPERTY(EditAnywhere) float GrainIntensity = 0.15f;
	UPROPERTY(EditAnywhere) float VignetteIntensity = 0.5f;
	UPROPERTY(EditAnywhere) float AutoExposureBias = 0.5f;
	UPROPERTY(EditAnywhere) float ChromaticAberrationIntensity = 0.3f;
};
