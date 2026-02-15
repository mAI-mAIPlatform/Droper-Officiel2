// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterRagdollComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UCharacterRagdollComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UCharacterRagdollComponent();
	UFUNCTION(BlueprintCallable) void ActivateRagdoll(FVector Impulse = FVector::ZeroVector, FName BoneName = NAME_None);
	UFUNCTION(BlueprintCallable) void DeactivateRagdoll();
	UFUNCTION(BlueprintCallable) void BlendToRagdoll(float BlendTime = 0.3f);
	UFUNCTION(BlueprintPure) bool IsRagdolling() const { return bIsRagdoll; }
protected:
	UPROPERTY(EditAnywhere, Category="Ragdoll") float ImpulseMultiplier = 5000.0f;
	bool bIsRagdoll = false;
};
