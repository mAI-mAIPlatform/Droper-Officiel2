// Copyright (c) 2026 mCompany. All Rights Reserved.

#include "Droper.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogDroper);

void FDroperModule::StartupModule()
{
	UE_LOG(LogDroper, Log, TEXT("Droper Module Started"));
}

void FDroperModule::ShutdownModule()
{
	UE_LOG(LogDroper, Log, TEXT("Droper Module Shutdown"));
}

IMPLEMENT_PRIMARY_GAME_MODULE(FDroperModule, Droper, "Droper");
