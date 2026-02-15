// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Gadgets/GadgetBase.h"
#include "GrenadeActor.generated.h"
UCLASS(Blueprintable) class DROPER_API AGrenadeActor : public AGadgetBase { GENERATED_BODY() public: AGrenadeActor(); virtual void Use(AActor* User) override; virtual void Detonate() override;
protected: UPROPERTY(EditAnywhere) float FuseTime = 3.5f; FTimerHandle FuseTimer; };
