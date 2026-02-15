// Copyright (c) 2026 mCompany. All Rights Reserved.

#include "DroperPlayerState.h"
#include "Net/UnrealNetwork.h"

ADroperPlayerState::ADroperPlayerState()
{
}

void ADroperPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADroperPlayerState, TeamId);
	DOREPLIFETIME(ADroperPlayerState, Kills);
	DOREPLIFETIME(ADroperPlayerState, Deaths);
	DOREPLIFETIME(ADroperPlayerState, Assists);
	DOREPLIFETIME(ADroperPlayerState, ExtractedLootValue);
	DOREPLIFETIME(ADroperPlayerState, bSurvivedRaid);
	DOREPLIFETIME(ADroperPlayerState, SelectedOperatorId);
	DOREPLIFETIME(ADroperPlayerState, DamageDealt);
}

void ADroperPlayerState::SetTeamId(int32 NewTeamId)
{
	if (HasAuthority())
	{
		TeamId = NewTeamId;
	}
}

void ADroperPlayerState::AddKill()
{
	if (!HasAuthority()) return;
	Kills++;
	OnStatChanged.Broadcast(FName("Kills"), Kills);
}

void ADroperPlayerState::AddDeath()
{
	if (!HasAuthority()) return;
	Deaths++;
	OnStatChanged.Broadcast(FName("Deaths"), Deaths);
}

void ADroperPlayerState::AddAssist()
{
	if (!HasAuthority()) return;
	Assists++;
	OnStatChanged.Broadcast(FName("Assists"), Assists);
}

void ADroperPlayerState::AddExtractedLootValue(int32 Value)
{
	if (!HasAuthority()) return;
	ExtractedLootValue += Value;
	OnStatChanged.Broadcast(FName("ExtractedLootValue"), ExtractedLootValue);
}

void ADroperPlayerState::SetSurvived(bool bSurvived)
{
	if (HasAuthority())
	{
		bSurvivedRaid = bSurvived;
	}
}

void ADroperPlayerState::Server_SelectOperator_Implementation(const FName& OperatorId)
{
	SelectedOperatorId = OperatorId;
}

void ADroperPlayerState::AddDamageDealt(float Amount)
{
	if (HasAuthority())
	{
		DamageDealt += Amount;
	}
}
