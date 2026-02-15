// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AudioManager.generated.h"

UCLASS()
class DROPER_API UAudioManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& C) override;
	UFUNCTION(BlueprintCallable) void PlayFootstepSound(FVector Location, FName SurfaceType);
	UFUNCTION(BlueprintCallable) void PlayWeaponSound(FVector Location, USoundBase* Sound, float VolumeModifier = 1.0f);
	UFUNCTION(BlueprintCallable) void SetMasterVolume(float Volume);
	UFUNCTION(BlueprintCallable) void SetSFXVolume(float Volume);
	UFUNCTION(BlueprintCallable) void SetMusicVolume(float Volume);
	UFUNCTION(BlueprintCallable) void ApplyOcclusion(UAudioComponent* Audio, float OcclusionFactor);
protected:
	UPROPERTY() float MasterVolume = 1.0f;
	UPROPERTY() float SFXVolume = 1.0f;
	UPROPERTY() float MusicVolume = 0.5f;
};
