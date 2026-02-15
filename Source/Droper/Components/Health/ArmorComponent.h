// Copyright (c) 2026 mCompany. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ArmorComponent.generated.h"

UENUM(BlueprintType) enum class EArmorZone : uint8 { Front, Back, LeftSide, RightSide };

USTRUCT(BlueprintType) struct FArmorPlate { GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EArmorZone Zone = EArmorZone::Front;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MaxDurability = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float CurrentDurability = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float ArmorClass = 4.0f; // 1-6 rating
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float DamageReduction = 0.5f;
	float GetDurabilityPercent() const { return MaxDurability > 0 ? CurrentDurability / MaxDurability : 0.0f; }
	bool IsDestroyed() const { return CurrentDurability <= 0.0f; }
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPER_API UArmorComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UArmorComponent();
	UFUNCTION(BlueprintCallable) float ProcessDamage(float IncomingDamage, float ArmorPierce, FVector HitDirection);
	UFUNCTION(BlueprintCallable) void RepairArmor(EArmorZone Zone, float Amount);
	UFUNCTION(BlueprintPure) float GetArmorDurability(EArmorZone Zone) const;
	UFUNCTION(BlueprintPure) bool HasArmor() const { return Plates.Num() > 0; }

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArmorDamaged, EArmorZone, Zone, float, RemainingDurability);
	UPROPERTY(BlueprintAssignable) FOnArmorDamaged OnArmorDamaged;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnArmorDestroyed, EArmorZone, Zone);
	UPROPERTY(BlueprintAssignable) FOnArmorDestroyed OnArmorDestroyed;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Armor") TArray<FArmorPlate> Plates;
	EArmorZone DetermineHitZone(FVector HitDirection) const;
};
