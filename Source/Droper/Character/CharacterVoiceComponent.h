// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterVoiceComponent.generated.h"

UENUM(BlueprintType)
enum class EVoiceBark : uint8 { Spotted, Reloading, TakingFire, Grenade, Healing, Down, Callout, Affirmative, Negative };

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UCharacterVoiceComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UCharacterVoiceComponent();
	UFUNCTION(BlueprintCallable, Category="Droper|Voice") void PlayBark(EVoiceBark BarkType);
	UFUNCTION(BlueprintCallable, Category="Droper|Voice") void SetVoicePack(USoundBase* NewPack) { VoicePack = NewPack; }
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Droper|Voice") TObjectPtr<USoundBase> VoicePack;
	UPROPERTY(EditAnywhere, Category="Droper|Voice") float BarkCooldown = 3.0f;
	float LastBarkTime = 0.0f;
};
