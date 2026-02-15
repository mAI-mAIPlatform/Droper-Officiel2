// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "VehicleBase.h"
ADroperVehicleBase::ADroperVehicleBase() { Seats.SetNum(MaxSeats); }
bool ADroperVehicleBase::EnterVehicle(AActor* P, int32 Idx) { if (!Seats.IsValidIndex(Idx) || Seats[Idx].IsValid()) return false; Seats[Idx] = P; return true; }
void ADroperVehicleBase::ExitVehicle(int32 Idx) { if (Seats.IsValidIndex(Idx)) Seats[Idx] = nullptr; }
AActor* ADroperVehicleBase::GetPassenger(int32 Idx) const { return Seats.IsValidIndex(Idx) ? Seats[Idx].Get() : nullptr; }
float ADroperVehicleBase::GetHealthPercent() const { return MaxHealth > 0 ? CurrentHealth / MaxHealth : 0; }
void ADroperVehicleBase::ApplyVehicleDamage(float D, FVector L) { CurrentHealth = FMath::Max(0.0f, CurrentHealth - D); }
