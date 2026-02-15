// Copyright (c) 2026 mCompany. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Types/AnimationTypes.h"
#include "DroperAnimInstance.generated.h"

UCLASS()
class DROPER_API UDroperAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly, Category = "Droper|Animation") float Speed = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Droper|Animation") float Direction = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Droper|Animation") bool bIsInAir = false;
	UPROPERTY(BlueprintReadOnly, Category = "Droper|Animation") bool bIsCrouching = false;
	UPROPERTY(BlueprintReadOnly, Category = "Droper|Animation") bool bIsSprinting = false;
	UPROPERTY(BlueprintReadOnly, Category = "Droper|Animation") bool bIsADS = false;
	UPROPERTY(BlueprintReadOnly, Category = "Droper|Animation") bool bIsAlive = true;
	UPROPERTY(BlueprintReadOnly, Category = "Droper|Animation") bool bIsDowned = false;
	UPROPERTY(BlueprintReadOnly, Category = "Droper|Animation") float AimPitch = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Droper|Animation") float AimYaw = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Droper|Animation") float LeanAngle = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Droper|Animation") ELocomotionState LocomotionState = ELocomotionState::Idle;
	UPROPERTY(BlueprintReadOnly, Category = "Droper|Animation") EWeaponPose WeaponPose = EWeaponPose::Unarmed;
	UPROPERTY(BlueprintReadOnly, Category = "Droper|Animation") EUpperBodyState UpperBodyState = EUpperBodyState::None;
	UPROPERTY(BlueprintReadOnly, Category = "Droper|Animation") FProceduralRecoilData RecoilData;

protected:
	UPROPERTY() TWeakObjectPtr<class ADroperCharacterBase> OwnerCharacter;
	void UpdateLocomotionState();
};
