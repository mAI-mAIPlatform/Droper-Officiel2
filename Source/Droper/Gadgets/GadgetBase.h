// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GadgetBase.generated.h"

UENUM(BlueprintType) enum class EGadgetType : uint8 { Grenade, Flashbang, Smoke, Mine, C4, Drone, Shield, Sensor };

UCLASS(Abstract, Blueprintable)
class DROPER_API AGadgetBase : public AActor
{
	GENERATED_BODY()
public:
	AGadgetBase();
	UFUNCTION(BlueprintCallable) virtual void Use(AActor* User);
	UFUNCTION(BlueprintCallable) virtual void Detonate();
	UFUNCTION(BlueprintPure) EGadgetType GetGadgetType() const { return GadgetType; }
	UFUNCTION(BlueprintPure) int32 GetCharges() const { return CurrentCharges; }
protected:
	UPROPERTY(EditAnywhere) EGadgetType GadgetType = EGadgetType::Grenade;
	UPROPERTY(EditAnywhere) int32 MaxCharges = 1;
	UPROPERTY(EditAnywhere) int32 CurrentCharges = 1;
	UPROPERTY(EditAnywhere) float ActivationDelay = 3.0f;
	UPROPERTY(EditAnywhere) float EffectRadius = 500.0f;
	UPROPERTY(EditAnywhere) float Damage = 0.0f;
	UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> GadgetMesh;
};
