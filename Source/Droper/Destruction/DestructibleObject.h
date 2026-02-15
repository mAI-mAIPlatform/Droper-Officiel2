// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleObject.generated.h"

UCLASS(Blueprintable)
class DROPER_API ADestructibleObject : public AActor
{
	GENERATED_BODY()
public:
	ADestructibleObject();
	UFUNCTION(BlueprintCallable) void ApplyDamage(float D, FVector ImpactPoint, FVector ImpactNormal);
	UFUNCTION(BlueprintPure) float GetHealthPercent() const;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDestroyed_Obj);
	UPROPERTY(BlueprintAssignable) FOnDestroyed_Obj OnDestructionComplete;
protected:
	UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> MeshComp;
	UPROPERTY(EditAnywhere) float MaxHealth = 200.0f;
	float CurrentHealth = 200.0f;
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMesh> DestroyedMesh;
};
