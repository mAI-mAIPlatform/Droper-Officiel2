// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Types/EnvironmentTypes.h"
#include "WeatherSubsystem.generated.h"

UCLASS()
class DROPER_API UWeatherSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& C) override;
	virtual void Tick(float DeltaTime) override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override { return WorldType == EWorldType::Game || WorldType == EWorldType::PIE; }
	UFUNCTION(BlueprintCallable) void SetWeatherState(EWeatherState State);
	UFUNCTION(BlueprintPure) EWeatherState GetWeatherState() const { return CurrentWeather; }
	UFUNCTION(BlueprintCallable) void SetTimeOfDay(ETimeOfDay Time);
	UFUNCTION(BlueprintPure) ETimeOfDay GetTimeOfDay() const { return CurrentTime; }
	UFUNCTION(BlueprintPure) FVector GetWindDirection() const { return WindDirection; }
	UFUNCTION(BlueprintPure) float GetWindSpeed() const { return WindSpeed; }
protected:
	EWeatherState CurrentWeather = EWeatherState::Clear;
	ETimeOfDay CurrentTime = ETimeOfDay::Day;
	FVector WindDirection = FVector(1, 0, 0);
	float WindSpeed = 0.0f;
	UPROPERTY(EditAnywhere) float WeatherTransitionTime = 30.0f;
};
