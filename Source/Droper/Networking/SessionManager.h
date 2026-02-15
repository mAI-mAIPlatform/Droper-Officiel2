// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SessionManager.generated.h"

UCLASS()
class DROPER_API USessionManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& C) override;
	UFUNCTION(BlueprintCallable) void HostSession(FName SessionName, int32 MaxPlayers, bool bIsLAN);
	UFUNCTION(BlueprintCallable) void JoinSession(const FString& SessionId);
	UFUNCTION(BlueprintCallable) void LeaveSession();
	UFUNCTION(BlueprintCallable) void FindSessions(bool bIsLAN);
	UFUNCTION(BlueprintPure) bool IsInSession() const { return bInSession; }
protected:
	bool bInSession = false;
};
