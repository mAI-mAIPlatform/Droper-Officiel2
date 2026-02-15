// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "VehicleBase.generated.h"

UCLASS(Abstract, Blueprintable)
class DROPER_API ADroperVehicleBase : public AWheeledVehiclePawn
{
	GENERATED_BODY()
public:
	ADroperVehicleBase();
	UFUNCTION(BlueprintCallable) bool EnterVehicle(AActor* Passenger, int32 SeatIndex);
	UFUNCTION(BlueprintCallable) void ExitVehicle(int32 SeatIndex);
	UFUNCTION(BlueprintPure) AActor* GetPassenger(int32 SeatIndex) const;
	UFUNCTION(BlueprintPure) int32 GetSeatCount() const { return Seats.Num(); }
	UFUNCTION(BlueprintPure) float GetHealthPercent() const;
	UFUNCTION(BlueprintCallable) void ApplyVehicleDamage(float Damage, FVector HitLocation);
protected:
	TArray<TWeakObjectPtr<AActor>> Seats;
	UPROPERTY(EditAnywhere) int32 MaxSeats = 4;
	UPROPERTY(EditAnywhere) float MaxHealth = 1000.0f;
	float CurrentHealth = 1000.0f;
};
