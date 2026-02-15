// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "SessionManager.h"
void USessionManager::Initialize(FSubsystemCollectionBase& C) { Super::Initialize(C); }
void USessionManager::HostSession(FName N, int32 M, bool L) { bInSession = true; }
void USessionManager::JoinSession(const FString& S) { bInSession = true; }
void USessionManager::LeaveSession() { bInSession = false; }
void USessionManager::FindSessions(bool L) {}
