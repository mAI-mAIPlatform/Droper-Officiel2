// Copyright (c) 2026 mCompany. All Rights Reserved.

#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	InitializeBodyParts();
}

void UHealthComponent::InitializeBodyParts()
{
	if (BodyPartMap.Num() > 0) return;

	auto AddPart = [this](EBodyPart Part, float HP) {
		FBodyPartHealth Data;
		Data.CurrentHP = HP; Data.MaxHP = HP;
		BodyPartMap.Add(Part, Data);
	};

	AddPart(EBodyPart::Head, 35.0f);
	AddPart(EBodyPart::Neck, 35.0f);
	AddPart(EBodyPart::UpperTorso, 85.0f);
	AddPart(EBodyPart::LowerTorso, 70.0f);
	AddPart(EBodyPart::LeftArm, 60.0f);
	AddPart(EBodyPart::RightArm, 60.0f);
	AddPart(EBodyPart::LeftLeg, 65.0f);
	AddPart(EBodyPart::RightLeg, 65.0f);
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!bIsDead) TickHemorrhage(DeltaTime);
}

void UHealthComponent::ApplyLocalizedDamage(const FLocalizedDamageEvent& DamageEvent)
{
	if (bIsDead) return;

	FBodyPartHealth* Part = BodyPartMap.Find(DamageEvent.TargetBodyPart);
	if (!Part) return;

	float FinalDamage = ApplyDamageModifiers(DamageEvent.TargetBodyPart, DamageEvent.RawDamage, DamageEvent.ArmorPierce);
	Part->CurrentHP = FMath::Max(0.0f, Part->CurrentHP - FinalDamage);

	OnBodyPartDamaged.Broadcast(DamageEvent.TargetBodyPart, FinalDamage, Part->CurrentHP);
	OnHealthChanged.Broadcast(GetOverallHealthPercent());

	// Roll for critical states
	if (FMath::FRand() < DamageEvent.HemorrhageChance)
	{
		AddCriticalState(DamageEvent.TargetBodyPart, ECriticalState::Hemorrhage);
	}
	if (FMath::FRand() < DamageEvent.FractureChance)
	{
		AddCriticalState(DamageEvent.TargetBodyPart, ECriticalState::Fracture);
	}
	if (FMath::FRand() < DamageEvent.ConcussionChance)
	{
		AddCriticalState(DamageEvent.TargetBodyPart, ECriticalState::Concussion);
	}

	CheckDeathCondition();
}

float UHealthComponent::ApplyDamageModifiers(EBodyPart Part, float RawDamage, float ArmorPierce) const
{
	const FBodyPartHealth* Data = BodyPartMap.Find(Part);
	if (!Data) return RawDamage;

	float ArmorAbsorption = Data->ArmorModifier * (1.0f - ArmorPierce);
	return RawDamage * (1.0f - ArmorAbsorption);
}

void UHealthComponent::HealBodyPart(EBodyPart Part, float Amount)
{
	FBodyPartHealth* Data = BodyPartMap.Find(Part);
	if (Data) { Data->CurrentHP = FMath::Min(Data->MaxHP, Data->CurrentHP + Amount); OnHealthChanged.Broadcast(GetOverallHealthPercent()); }
}

void UHealthComponent::HealAll(float Amount)
{
	for (auto& Pair : BodyPartMap) { Pair.Value.CurrentHP = FMath::Min(Pair.Value.MaxHP, Pair.Value.CurrentHP + Amount); }
	OnHealthChanged.Broadcast(GetOverallHealthPercent());
}

float UHealthComponent::GetOverallHealthPercent() const
{
	float Total = 0.0f, Max = 0.0f;
	for (const auto& Pair : BodyPartMap) { Total += Pair.Value.CurrentHP; Max += Pair.Value.MaxHP; }
	return Max > 0.0f ? Total / Max : 0.0f;
}

float UHealthComponent::GetBodyPartHealthPercent(EBodyPart Part) const
{
	const FBodyPartHealth* Data = BodyPartMap.Find(Part);
	return Data ? Data->GetHealthPercent() : 0.0f;
}

const FBodyPartHealth& UHealthComponent::GetBodyPartHealth(EBodyPart Part) const
{
	static FBodyPartHealth Empty;
	const FBodyPartHealth* Data = BodyPartMap.Find(Part);
	return Data ? *Data : Empty;
}

bool UHealthComponent::HasCriticalState(EBodyPart Part, ECriticalState State) const
{
	const FBodyPartHealth* Data = BodyPartMap.Find(Part);
	return Data ? Data->HasCriticalState(State) : false;
}

bool UHealthComponent::IsAnyPartDestroyed() const
{
	for (const auto& Pair : BodyPartMap) { if (Pair.Value.IsDestroyed()) return true; }
	return false;
}

void UHealthComponent::AddCriticalState(EBodyPart Part, ECriticalState State)
{
	FBodyPartHealth* Data = BodyPartMap.Find(Part);
	if (Data && !Data->HasCriticalState(State))
	{
		Data->AddCriticalState(State);
		OnCriticalStateChanged.Broadcast(Part, State);
	}
}

void UHealthComponent::RemoveCriticalState(EBodyPart Part, ECriticalState State)
{
	FBodyPartHealth* Data = BodyPartMap.Find(Part);
	if (Data) Data->RemoveCriticalState(State);
}

void UHealthComponent::TickHemorrhage(float DeltaTime)
{
	for (auto& Pair : BodyPartMap)
	{
		if (Pair.Value.HasCriticalState(ECriticalState::Hemorrhage))
		{
			Pair.Value.CurrentHP -= HemorrhageDamagePerSecond * DeltaTime;
			if (Pair.Value.CurrentHP <= 0.0f)
			{
				Pair.Value.CurrentHP = 0.0f;
				CheckDeathCondition();
			}
		}
	}
}

void UHealthComponent::CheckDeathCondition()
{
	if (bIsDead) return;

	const FBodyPartHealth* Head = BodyPartMap.Find(EBodyPart::Head);
	if (Head && Head->CurrentHP <= HeadDeathThreshold)
	{
		bIsDead = true;
		OnDeath.Broadcast();
		return;
	}

	// Death if upper torso is destroyed
	const FBodyPartHealth* Torso = BodyPartMap.Find(EBodyPart::UpperTorso);
	if (Torso && Torso->IsDestroyed())
	{
		bIsDead = true;
		OnDeath.Broadcast();
		return;
	}

	// Death if overall health below threshold
	if (GetOverallHealthPercent() <= 0.05f)
	{
		bIsDead = true;
		OnDeath.Broadcast();
	}
}
