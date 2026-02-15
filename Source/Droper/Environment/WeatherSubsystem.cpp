// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "WeatherSubsystem.h"
void UWeatherSubsystem::Initialize(FSubsystemCollectionBase& C) { Super::Initialize(C); }
void UWeatherSubsystem::Tick(float DT) { /* Interpolate weather transitions */ }
void UWeatherSubsystem::SetWeatherState(EWeatherState S) { CurrentWeather = S; }
void UWeatherSubsystem::SetTimeOfDay(ETimeOfDay T) { CurrentTime = T; }
