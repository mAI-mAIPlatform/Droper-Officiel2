// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "CoverSystem.h"
void UCoverSystem::Initialize(FSubsystemCollectionBase& C) { Super::Initialize(C); }
void UCoverSystem::RegisterCoverPoint(const FCoverPoint& P) { CoverPoints.Add(P); }
FCoverPoint UCoverSystem::FindBestCover(FVector From, FVector Threat, float MaxDist) const
{
	FCoverPoint Best; float BestScore = -1.0f;
	for (const auto& P : CoverPoints) {
		if (P.bIsOccupied) continue;
		float Dist = FVector::Dist(From, P.Location);
		if (Dist > MaxDist) continue;
		float ThreatDot = FVector::DotProduct((Threat - P.Location).GetSafeNormal(), P.Normal);
		float Score = (1.0f - Dist/MaxDist) + (ThreatDot > 0 ? ThreatDot : 0);
		if (Score > BestScore) { Best = P; BestScore = Score; }
	}
	return Best;
}
void UCoverSystem::OccupyCover(int32 I) { if (CoverPoints.IsValidIndex(I)) CoverPoints[I].bIsOccupied = true; }
void UCoverSystem::ReleaseCover(int32 I) { if (CoverPoints.IsValidIndex(I)) CoverPoints[I].bIsOccupied = false; }
