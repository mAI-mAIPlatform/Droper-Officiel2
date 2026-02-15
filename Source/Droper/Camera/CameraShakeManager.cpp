// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "CameraShakeManager.h"
#include "GameFramework/PlayerController.h"
UCameraShakeManager::UCameraShakeManager() { PrimaryComponentTick.bCanEverTick = false; }
void UCameraShakeManager::PlayShake(TSubclassOf<UCameraShakeBase> SC, float S)
{
	APlayerController* PC = Cast<APlayerController>(Cast<APawn>(GetOwner())->GetController());
	if (PC && SC) PC->ClientStartCameraShake(SC, S);
}
void UCameraShakeManager::PlayMovementShake(float Speed) { PlayShake(Speed > 400 ? SprintShake : WalkShake, Speed / 600.0f); }
void UCameraShakeManager::PlayRecoilShake(float I) { PlayShake(FireShake, I); }
void UCameraShakeManager::PlayExplosionShake(float D, float MR) { float S = FMath::Clamp(1.0f - D/MR, 0.0f, 1.0f); PlayShake(ExplosionShake, S); }
