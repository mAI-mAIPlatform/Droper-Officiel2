// Copyright (c) 2026 mCompany. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Types/DamageTypes.h"
#include "DroperCharacterBase.generated.h"

class UHealthComponent;

/**
 * ADroperCharacterBase
 * 
 * Abstract base for both player and AI characters.
 * Provides skeletal mesh, localized health component, death flow, and replicated state.
 */
UCLASS(Abstract)
class DROPER_API ADroperCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ADroperCharacterBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// --- Health ---
	UFUNCTION(BlueprintPure, Category = "Droper|Character")
	UHealthComponent* GetHealthComponent() const { return HealthComp; }

	UFUNCTION(BlueprintPure, Category = "Droper|Character")
	bool IsAlive() const { return bIsAlive; }

	UFUNCTION(BlueprintPure, Category = "Droper|Character")
	bool IsDowned() const { return bIsDowned; }

	// --- Localized Damage ---
	UFUNCTION(BlueprintCallable, Category = "Droper|Character")
	virtual void ApplyLocalizedDamage(const FLocalizedDamageEvent& DamageEvent);

	// --- Death ---
	UFUNCTION(BlueprintCallable, Authority, Category = "Droper|Character")
	virtual void Die(AController* Killer, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, Authority, Category = "Droper|Character")
	virtual void EnterDownedState();

	// --- Team ---
	UFUNCTION(BlueprintPure, Category = "Droper|Character")
	int32 GetTeamId() const { return TeamId; }

	UFUNCTION(BlueprintCallable, Authority, Category = "Droper|Character")
	void SetTeamId(int32 NewTeamId);

	// --- Delegates ---
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCharacterDied, ADroperCharacterBase*, Character, AController*, Killer);
	UPROPERTY(BlueprintAssignable, Category = "Droper|Character")
	FOnCharacterDied OnCharacterDied;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterDowned, ADroperCharacterBase*, Character);
	UPROPERTY(BlueprintAssignable, Category = "Droper|Character")
	FOnCharacterDowned OnCharacterDowned;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Droper|Components")
	TObjectPtr<UHealthComponent> HealthComp;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Droper|Character")
	bool bIsAlive = true;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Droper|Character")
	bool bIsDowned = false;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Droper|Character")
	int32 TeamId = INDEX_NONE;

	UFUNCTION()
	virtual void OnHealthDepleted();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_OnDeath();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_OnDowned();

	virtual void HandleDeath();
	virtual void HandleDowned();

	// Ragdoll
	void EnableRagdoll();
	void DisableRagdoll();
};
