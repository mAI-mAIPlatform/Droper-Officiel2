// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "ProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	CollisionComp->InitSphereRadius(2.0f);
	CollisionComp->SetCollisionProfileName(TEXT("Projectile"));
	SetRootComponent(CollisionComp);
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = GravityScale;
	InitialLifeSpan = LifeSpan;
}

void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Apply drag
	if (ProjectileMovement)
	{
		float Speed = ProjectileMovement->Velocity.Size();
		float DragForce = DragCoefficient * Speed * Speed;
		FVector DragDir = -ProjectileMovement->Velocity.GetSafeNormal();
		ProjectileMovement->Velocity += DragDir * DragForce * DeltaTime;
	}
}

void AProjectileBase::InitVelocity(FVector Direction, float Speed)
{
	if (ProjectileMovement) ProjectileMovement->Velocity = Direction * Speed;
}

void AProjectileBase::OnImpact(const FHitResult& Hit) { Destroy(); }
