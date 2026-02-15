// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "SquadManager.h"
USquadManager::USquadManager() { PrimaryComponentTick.bCanEverTick = false; }
void USquadManager::AddMember(AActor* M) { if (Members.Num() < MaxSquadSize) Members.Add(M); }
void USquadManager::RemoveMember(AActor* M) { Members.RemoveAll([M](const TWeakObjectPtr<AActor>& A) { return A.Get() == M; }); }
void USquadManager::IssueOrder(FName OrderType, FVector TargetLocation) { /* Broadcast to members via blackboard */ }
