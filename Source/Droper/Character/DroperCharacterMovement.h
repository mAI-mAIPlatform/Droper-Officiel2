// Copyright (c) 2026 mCompany. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DroperCharacterMovement.generated.h"

/**
 * Custom character movement: stamina drain, lean tilt, vault, prone, slide, weight-based inertia.
 */
UCLASS()
class DROPER_API UDroperCharacterMovement : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UDroperCharacterMovement();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual float GetMaxSpeed() const override;
	virtual float GetMaxAcceleration() const override;

	// --- Stamina Integration ---
	void SetStaminaPercent(float Percent);
	void SetWeightModifier(float Modifier);

	// --- Prone ---
	UFUNCTION(BlueprintCallable, Category = "Droper|Movement")
	void EnterProne();

	UFUNCTION(BlueprintCallable, Category = "Droper|Movement")
	void ExitProne();

	UFUNCTION(BlueprintPure, Category = "Droper|Movement")
	bool IsProneState() const { return bIsProne; }

	// --- Slide ---
	UFUNCTION(BlueprintCallable, Category = "Droper|Movement")
	void StartSlide();

	UFUNCTION(BlueprintPure, Category = "Droper|Movement")
	bool IsSliding() const { return bIsSliding; }

	// --- Properties ---
	UPROPERTY(EditDefaultsOnly, Category = "Droper|Movement")
	float SprintSpeed = 600.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Droper|Movement")
	float WalkSpeed = 450.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Droper|Movement")
	float CrouchSpeed = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Droper|Movement")
	float ProneSpeed = 80.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Droper|Movement")
	float ADSSpeed = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Droper|Movement")
	float SlideInitialSpeed = 800.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Droper|Movement")
	float SlideDeceleration = 400.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Droper|Movement")
	float SlideMinSpeed = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Droper|Movement")
	float ProneCapsuleHalfHeight = 30.0f;

protected:
	bool bIsProne = false;
	bool bIsSliding = false;
	float CurrentSlideSpeed = 0.0f;
	float StaminaPercent = 1.0f;
	float WeightModifier = 1.0f; // Higher = slower
	float OriginalCapsuleHalfHeight = 0.0f;

	void UpdateSlide(float DeltaTime);
};
