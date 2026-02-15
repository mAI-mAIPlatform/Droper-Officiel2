// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponMountComponent.generated.h"
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UWeaponMountComponent : public UActorComponent { GENERATED_BODY() public:
	UWeaponMountComponent();
	UFUNCTION(BlueprintCallable) bool TryMount();
	UFUNCTION(BlueprintCallable) void Unmount();
	UFUNCTION(BlueprintPure) bool IsMounted() const { return bIsMounted; }
	UFUNCTION(BlueprintPure) float GetRecoilReduction() const { return bIsMounted ? MountedRecoilReduction : 0.0f; }
protected: bool bIsMounted = false;
	UPROPERTY(EditAnywhere) float MountTraceDistance = 80.0f; UPROPERTY(EditAnywhere) float MountedRecoilReduction = 0.6f; };
