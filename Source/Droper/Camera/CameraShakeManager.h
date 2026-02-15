// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraShakeManager.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UCameraShakeManager : public UActorComponent
{
	GENERATED_BODY()
public:
	UCameraShakeManager();
	UFUNCTION(BlueprintCallable) void PlayShake(TSubclassOf<UCameraShakeBase> ShakeClass, float Scale = 1.0f);
	UFUNCTION(BlueprintCallable) void PlayMovementShake(float Speed);
	UFUNCTION(BlueprintCallable) void PlayRecoilShake(float Intensity);
	UFUNCTION(BlueprintCallable) void PlayExplosionShake(float Distance, float MaxRange);
protected:
	UPROPERTY(EditAnywhere) TSubclassOf<UCameraShakeBase> WalkShake;
	UPROPERTY(EditAnywhere) TSubclassOf<UCameraShakeBase> SprintShake;
	UPROPERTY(EditAnywhere) TSubclassOf<UCameraShakeBase> FireShake;
	UPROPERTY(EditAnywhere) TSubclassOf<UCameraShakeBase> ExplosionShake;
};
