// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "FractureEffect.h"
UFractureEffect::UFractureEffect() { PrimaryComponentTick.bCanEverTick = false; }
void UFractureEffect::ApplyFracture(FName LimbBone) { FracturedBones.Add(LimbBone); }
void UFractureEffect::Splint(FName LimbBone, float HealTime) { FracturedBones.Remove(LimbBone); }
bool UFractureEffect::HasFracture(FName LimbBone) const { return FracturedBones.Contains(LimbBone); }
float UFractureEffect::GetSpeedPenalty() const { return FracturedBones.Num() * SpeedPenaltyPerFracture; }
float UFractureEffect::GetSwayPenalty() const { return FracturedBones.Num() * SwayPenaltyPerFracture; }
