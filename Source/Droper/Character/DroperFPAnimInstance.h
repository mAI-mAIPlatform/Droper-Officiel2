// Copyright (c) 2026 mCompany. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Types/AnimationTypes.h"
#include "DroperFPAnimInstance.generated.h"

UCLASS()
class DROPER_API UDroperFPAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly) EWeaponPose WeaponPose = EWeaponPose::Unarmed;
	UPROPERTY(BlueprintReadOnly) bool bIsADS = false;
	UPROPERTY(BlueprintReadOnly) bool bIsReloading = false;
	UPROPERTY(BlueprintReadOnly) FProceduralRecoilData RecoilData;
	UPROPERTY(BlueprintReadOnly) float SwayX = 0.0f;
	UPROPERTY(BlueprintReadOnly) float SwayY = 0.0f;
	UPROPERTY(BlueprintReadOnly) float SprintBlend = 0.0f;
protected:
	UPROPERTY() TWeakObjectPtr<class ADroperCharacter> OwnerCharacter;
};
