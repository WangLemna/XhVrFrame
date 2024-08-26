// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Base/Actor/XhActorBase.h"
#include "AN_SetHiddenXhActor.generated.h"

/**
 * 
 */
UCLASS()
class XHVR_API UAN_SetHiddenXhActor : public UAnimNotify
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhSettings")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhSettings")
	TSubclassOf<AXhActorBase> MyActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhSettings")
	FName TagName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhSettings")
	bool bHidden;

	UE_DEPRECATED(5.0, "Please use the other Notify function instead")
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};