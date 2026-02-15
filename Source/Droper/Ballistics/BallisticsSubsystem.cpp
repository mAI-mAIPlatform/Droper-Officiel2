// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "BallisticsSubsystem.h"
void UBallisticsSubsystem::Initialize(FSubsystemCollectionBase& Collection) { Super::Initialize(Collection); }
FVector UBallisticsSubsystem::ApplyWindToVelocity(FVector Velocity, float DeltaTime) const
{
	return Velocity + WindVector * DeltaTime;
}
float UBallisticsSubsystem::CalculateBulletDrop(float Distance, float MuzzleVelocity) const
{
	float FlightTime = Distance / FMath::Max(MuzzleVelocity, 1.0f);
	return 0.5f * 980.0f * FlightTime * FlightTime; // cm/s² gravity
}
