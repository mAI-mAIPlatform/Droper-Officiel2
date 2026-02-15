// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Ballistics/ProjectileBase.h"
#include "BulletProjectile.generated.h"
UCLASS(Blueprintable) class DROPER_API ABulletProjectile : public AProjectileBase { GENERATED_BODY() public: ABulletProjectile();
	virtual void OnImpact(const FHitResult& Hit) override;
protected: UPROPERTY(EditAnywhere) float PenetrationPower = 1.0f; UPROPERTY(EditAnywhere) float RicochetAngleThreshold = 15.0f; };
