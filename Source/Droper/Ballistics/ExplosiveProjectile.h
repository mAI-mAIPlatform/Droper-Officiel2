// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Ballistics/ProjectileBase.h"
#include "ExplosiveProjectile.generated.h"
UCLASS(Blueprintable) class DROPER_API AExplosiveProjectile : public AProjectileBase { GENERATED_BODY() public: AExplosiveProjectile();
	virtual void OnImpact(const FHitResult& Hit) override;
	void Explode();
protected: UPROPERTY(EditAnywhere) float ExplosionRadius = 500.0f; UPROPERTY(EditAnywhere) float ExplosionDamage = 150.0f;
	UPROPERTY(EditAnywhere) TObjectPtr<class UNiagaraSystem> ExplosionVFX; UPROPERTY(EditAnywhere) TObjectPtr<USoundBase> ExplosionSFX; };
