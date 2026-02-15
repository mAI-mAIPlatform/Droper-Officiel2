// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "ProgressionSubsystem.h"
void UProgressionSubsystem::Initialize(FSubsystemCollectionBase& C) { Super::Initialize(C); }
void UProgressionSubsystem::AddXP(int32 A) { CurrentXP += A; while (CurrentXP >= GetXPForNextLevel()) { CurrentXP -= GetXPForNextLevel(); Level++; OnLevelUp.Broadcast(Level); } }
int32 UProgressionSubsystem::GetXPForNextLevel() const { return 100 * Level * Level; } // Quadratic curve
void UProgressionSubsystem::UnlockItem(FName Id) { UnlockedItems.Add(Id); }
bool UProgressionSubsystem::IsItemUnlocked(FName Id) const { return UnlockedItems.Contains(Id); }
