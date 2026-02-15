// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/WeaponTypes.h"
#include "WeaponRecoilComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UWeaponRecoilComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UWeaponRecoilComponent();
	virtual void TickComponent(float DT, ELevelTick T, FActorComponentTickFunction* F) override;
	void ApplyRecoil(const FRecoilPattern& Pattern, int32 ShotIndex);
	void ResetRecoil();
	UFUNCTION(BlueprintPure) FVector2D GetCurrentRecoil() const { return CurrentRecoil; }
protected:
	FVector2D CurrentRecoil = FVector2D::ZeroVector;
	FVector2D TargetRecoil = FVector2D::ZeroVector;
	UPROPERTY(EditAnywhere) float RecoilRecoverySpeed = 8.0f;
	UPROPERTY(EditAnywhere) float RecoilInterpSpeed = 20.0f;
};
