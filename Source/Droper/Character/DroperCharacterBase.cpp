// Copyright (c) 2026 mCompany. All Rights Reserved.

#include "DroperCharacterBase.h"
#include "Droper/Droper.h"
#include "Components/Health/HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Net/UnrealNetwork.h"

ADroperCharacterBase::ADroperCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void ADroperCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (HealthComp)
	{
		HealthComp->OnDeath.AddDynamic(this, &ADroperCharacterBase::OnHealthDepleted);
	}
}

void ADroperCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADroperCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADroperCharacterBase, bIsAlive);
	DOREPLIFETIME(ADroperCharacterBase, bIsDowned);
	DOREPLIFETIME(ADroperCharacterBase, TeamId);
}

float ADroperCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!bIsAlive) return 0.0f;
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ADroperCharacterBase::ApplyLocalizedDamage(const FLocalizedDamageEvent& DamageEvent)
{
	if (!HasAuthority() || !bIsAlive) return;

	if (HealthComp)
	{
		HealthComp->ApplyLocalizedDamage(DamageEvent);
	}
}

// --------------------------------------------------
// Death & Downed
// --------------------------------------------------

void ADroperCharacterBase::Die(AController* Killer, AActor* DamageCauser)
{
	if (!HasAuthority() || !bIsAlive) return;

	bIsAlive = false;
	bIsDowned = false;

	OnCharacterDied.Broadcast(this, Killer);
	Multicast_OnDeath();

	UE_LOG(LogDroper, Log, TEXT("%s has died. Killer: %s"),
		*GetName(), Killer ? *Killer->GetName() : TEXT("None"));
}

void ADroperCharacterBase::EnterDownedState()
{
	if (!HasAuthority() || !bIsAlive || bIsDowned) return;

	bIsDowned = true;
	OnCharacterDowned.Broadcast(this);
	Multicast_OnDowned();
}

void ADroperCharacterBase::OnHealthDepleted()
{
	if (bIsDowned)
	{
		Die(nullptr, nullptr);
	}
	else
	{
		EnterDownedState();
	}
}

void ADroperCharacterBase::Multicast_OnDeath_Implementation()
{
	HandleDeath();
}

void ADroperCharacterBase::Multicast_OnDowned_Implementation()
{
	HandleDowned();
}

void ADroperCharacterBase::HandleDeath()
{
	EnableRagdoll();

	// Disable collision on capsule
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Disable movement
	GetCharacterMovement()->DisableMovement();
}

void ADroperCharacterBase::HandleDowned()
{
	// Slow movement, disable weapon
	GetCharacterMovement()->MaxWalkSpeed = 50.0f;
}

void ADroperCharacterBase::SetTeamId(int32 NewTeamId)
{
	if (HasAuthority())
	{
		TeamId = NewTeamId;
	}
}

// --------------------------------------------------
// Ragdoll
// --------------------------------------------------

void ADroperCharacterBase::EnableRagdoll()
{
	USkeletalMeshComponent* MeshComp = GetMesh();
	if (MeshComp)
	{
		MeshComp->SetSimulatePhysics(true);
		MeshComp->SetCollisionProfileName(TEXT("Ragdoll"));
	}
}

void ADroperCharacterBase::DisableRagdoll()
{
	USkeletalMeshComponent* MeshComp = GetMesh();
	if (MeshComp)
	{
		MeshComp->SetSimulatePhysics(false);
		MeshComp->SetCollisionProfileName(TEXT("CharacterMesh"));
		MeshComp->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}
