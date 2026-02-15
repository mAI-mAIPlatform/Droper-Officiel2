// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorActor.generated.h"

UENUM(BlueprintType) enum class EDoorState : uint8 { Closed, Opening, Open, Closing, Breached };

UCLASS(Blueprintable)
class DROPER_API ADoorActor : public AActor
{
	GENERATED_BODY()
public:
	ADoorActor();
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable) void Interact(AActor* Instigator);
	UFUNCTION(BlueprintCallable) void Breach(FVector ImpactPoint, float Force);
	UFUNCTION(BlueprintCallable) void PeekOpen(float Amount);
	UFUNCTION(BlueprintPure) EDoorState GetState() const { return DoorState; }
	UFUNCTION(BlueprintPure) bool IsLocked() const { return bIsLocked; }
	UFUNCTION(BlueprintCallable) void SetLocked(bool bLocked) { bIsLocked = bLocked; }
protected:
	UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> DoorMesh;
	UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> FrameMesh;
	UPROPERTY(EditAnywhere) float OpenAngle = 90.0f;
	UPROPERTY(EditAnywhere) float OpenSpeed = 3.0f;
	UPROPERTY(EditAnywhere) float BreachForce = 500.0f;
	float CurrentAngle = 0.0f, TargetAngle = 0.0f;
	EDoorState DoorState = EDoorState::Closed;
	bool bIsLocked = false;
	UPROPERTY(EditAnywhere) TObjectPtr<USoundBase> OpenSFX;
	UPROPERTY(EditAnywhere) TObjectPtr<USoundBase> BreachSFX;
};
