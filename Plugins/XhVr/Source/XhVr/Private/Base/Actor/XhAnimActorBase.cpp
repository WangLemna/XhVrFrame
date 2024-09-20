// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Actor/XhAnimActorBase.h"

void AXhAnimActorBase::CreateSkeletalMeshComps_Implementation()
{
	int32 Length = AnimData.SkeletalMeshes.Num();
	for (int32 i = 0; i < Length; i++)
	{
		USkeletalMeshComponent* SK_Comp = Cast<USkeletalMeshComponent>(AddComponentByClass(USkeletalMeshComponent::StaticClass(), false, FTransform(), false));
		SK_Comp->SetSkinnedAssetAndUpdate(AnimData.SkeletalMeshes[i]);
		SK_Comp->SetAnimationMode(EAnimationMode::AnimationSingleNode);
		SK_Comp->SetAnimation(AnimData.Anims[i]);
		SK_Comps.Add(SK_Comp);
	}
}

float AXhAnimActorBase::GetAnimMaxLength()
{
	float MaxLength = 0;;
	for (UAnimSequenceBase* Temp : AnimData.Anims)
	{
		MaxLength = FMath::Max(MaxLength, Temp->GetPlayLength());
	}
	return MaxLength;
}

void AXhAnimActorBase::PlayAnim()
{
	for (USkeletalMeshComponent* Temp : SK_Comps)
	{
		Temp->Play(false);
	}
}

void AXhAnimActorBase::BeginPlay()
{
	XH_BP_EXEC_B(XhBegin);
	Super::BeginPlay();
	CreateSkeletalMeshComps();
	XH_BP_EXEC_E(XhBegin);
}
