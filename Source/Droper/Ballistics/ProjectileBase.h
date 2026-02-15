// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UCLASS(Abstract, Blueprintable)
class DROPER_API AProjectileBase : public AActor
{
	GENERATED_BODY()
public:
	AProjectileBase();
	virtual void Tick(float DeltaTime) override;
	void InitVelocity(FVector Direction, float Speed);
	UFUNCTION(BlueprintPure) float GetCurrentSpeed() const { return Velocity.Size(); }
protected:
	virtual void OnImpact(const FHitResult& Hit);
	UPROPERTY(VisibleAnywhere) TObjectPtr<class USphereComponent> CollisionComp;
	UPROPERTY(VisibleAnywhere) TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;
	FVector Velocity;
	UPROPERTY(EditAnywhere) float Damage = 30.0f;
	UPROPERTY(EditAnywhere) float ArmorPierce = 0.3f;
	UPROPERTY(EditAnywhere) float LifeSpan = 5.0f;
	UPROPERTY(EditAnywhere) float DragCoefficient = 0.001f;
	UPROPERTY(EditAnywhere) float GravityScale = 1.0f;
};
