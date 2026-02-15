// Copyright (c) 2026 mCompany. All Rights Reserved.
#include "CharacterCosmeticComponent.h"
#include "GameFramework/Character.h"
#include "Engine/AssetManager.h"

UCharacterCosmeticComponent::UCharacterCosmeticComponent() { PrimaryComponentTick.bCanEverTick = false; }

void UCharacterCosmeticComponent::ApplySkin(TSoftObjectPtr<USkeletalMesh> SkinMesh)
{
	if (SkinMesh.IsNull()) return;
	UAssetManager::GetStreamableManager().RequestAsyncLoad(SkinMesh.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([this, SkinMesh]() {
			ACharacter* Owner = Cast<ACharacter>(GetOwner());
			if (Owner && Owner->GetMesh() && SkinMesh.Get()) { Owner->GetMesh()->SetSkeletalMesh(SkinMesh.Get()); }
		}));
}

void UCharacterCosmeticComponent::ApplyHelmet(TSoftObjectPtr<UStaticMesh> HelmetMesh)
{
	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if (!Owner) return;
	if (!HelmetMeshComp)
	{
		HelmetMeshComp = NewObject<UStaticMeshComponent>(Owner);
		HelmetMeshComp->AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, HelmetSocket);
		HelmetMeshComp->RegisterComponent();
	}
	UAssetManager::GetStreamableManager().RequestAsyncLoad(HelmetMesh.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([this, HelmetMesh]() { if (HelmetMeshComp && HelmetMesh.Get()) HelmetMeshComp->SetStaticMesh(HelmetMesh.Get()); }));
}

void UCharacterCosmeticComponent::ApplyGloves(TSoftObjectPtr<UMaterialInterface> GloveMaterial)
{
	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if (!Owner || !Owner->GetMesh()) return;
	UAssetManager::GetStreamableManager().RequestAsyncLoad(GloveMaterial.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([this, GloveMaterial]() {
			ACharacter* O = Cast<ACharacter>(GetOwner());
			if (O && O->GetMesh() && GloveMaterial.Get()) { O->GetMesh()->SetMaterial(1, GloveMaterial.Get()); }
		}));
}
