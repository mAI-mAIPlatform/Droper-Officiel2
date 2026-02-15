// Copyright (c) 2026 mCompany. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/DamageTypes.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnBodyPartDamaged, EBodyPart, Part, float, Damage, float, RemainingHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCriticalStateChanged, EBodyPart, Part, ECriticalState, State);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, OverallHealthPercent);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// --- Damage ---
	UFUNCTION(BlueprintCallable, Category = "Droper|Health")
	void ApplyLocalizedDamage(const FLocalizedDamageEvent& DamageEvent);

	UFUNCTION(BlueprintCallable, Category = "Droper|Health")
	void HealBodyPart(EBodyPart Part, float Amount);

	UFUNCTION(BlueprintCallable, Category = "Droper|Health")
	void HealAll(float Amount);

	// --- Queries ---
	UFUNCTION(BlueprintPure, Category = "Droper|Health")
	float GetOverallHealthPercent() const;

	UFUNCTION(BlueprintPure, Category = "Droper|Health")
	float GetBodyPartHealthPercent(EBodyPart Part) const;

	UFUNCTION(BlueprintPure, Category = "Droper|Health")
	const FBodyPartHealth& GetBodyPartHealth(EBodyPart Part) const;

	UFUNCTION(BlueprintPure, Category = "Droper|Health")
	bool HasCriticalState(EBodyPart Part, ECriticalState State) const;

	UFUNCTION(BlueprintPure, Category = "Droper|Health")
	bool IsAnyPartDestroyed() const;

	UFUNCTION(BlueprintPure, Category = "Droper|Health")
	bool IsDead() const { return bIsDead; }

	// --- Critical States ---
	UFUNCTION(BlueprintCallable, Category = "Droper|Health")
	void AddCriticalState(EBodyPart Part, ECriticalState State);

	UFUNCTION(BlueprintCallable, Category = "Droper|Health")
	void RemoveCriticalState(EBodyPart Part, ECriticalState State);

	// --- Delegates ---
	UPROPERTY(BlueprintAssignable) FOnDeath OnDeath;
	UPROPERTY(BlueprintAssignable) FOnBodyPartDamaged OnBodyPartDamaged;
	UPROPERTY(BlueprintAssignable) FOnCriticalStateChanged OnCriticalStateChanged;
	UPROPERTY(BlueprintAssignable) FOnHealthChanged OnHealthChanged;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Droper|Health")
	TMap<EBodyPart, FBodyPartHealth> BodyPartMap;

	UPROPERTY(EditAnywhere, Category = "Droper|Health")
	float HemorrhageDamagePerSecond = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Droper|Health")
	float HeadDeathThreshold = 0.0f; // Head at 0 = instant death

	bool bIsDead = false;

	void InitializeBodyParts();
	void TickHemorrhage(float DeltaTime);
	void CheckDeathCondition();
	float ApplyDamageModifiers(EBodyPart Part, float RawDamage, float ArmorPierce) const;
};
