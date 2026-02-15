// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "AudioManager.h"
#include "Kismet/GameplayStatics.h"
void UAudioManager::Initialize(FSubsystemCollectionBase& C) { Super::Initialize(C); }
void UAudioManager::PlayFootstepSound(FVector L, FName S) {}
void UAudioManager::PlayWeaponSound(FVector L, USoundBase* S, float V) { if (S) UGameplayStatics::PlaySoundAtLocation(GetWorld(), S, L, V * SFXVolume * MasterVolume); }
void UAudioManager::SetMasterVolume(float V) { MasterVolume = FMath::Clamp(V, 0.0f, 1.0f); }
void UAudioManager::SetSFXVolume(float V) { SFXVolume = FMath::Clamp(V, 0.0f, 1.0f); }
void UAudioManager::SetMusicVolume(float V) { MusicVolume = FMath::Clamp(V, 0.0f, 1.0f); }
void UAudioManager::ApplyOcclusion(UAudioComponent* A, float O) { if (A) A->SetVolumeMultiplier(1.0f - O * 0.8f); }
