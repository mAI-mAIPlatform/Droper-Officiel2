// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlindFireComponent.generated.h"
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UBlindFireComponent : public UActorComponent { GENERATED_BODY() public:
	UBlindFireComponent();
	UFUNCTION(BlueprintCallable) void StartBlindFire(bool bOverCover);
	UFUNCTION(BlueprintCallable) void StopBlindFire();
	UFUNCTION(BlueprintPure) bool IsBlindFiring() const { return bBlindFiring; }
	UFUNCTION(BlueprintPure) FVector GetBlindFireOffset() const;
protected: bool bBlindFiring = false; bool bOverCover = false;
	UPROPERTY(EditAnywhere) FVector OverCoverOffset = FVector(0, 0, 80); UPROPERTY(EditAnywhere) FVector SideCoverOffset = FVector(0, 60, 0);
	UPROPERTY(EditAnywhere) float BlindFireSpreadMult = 3.0f; };
