// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/Actor/XhActorBase.h"
#include "XhAnimActorBase.generated.h"

USTRUCT(BlueprintType)
struct FAnimData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform SpawnTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USkeletalMesh*> SkeletalMeshes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAnimSequenceBase*> Anims;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform PlayerTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDAB_Struct ExtraData;
	FAnimData()
		: SpawnTransform(FTransform())
		, PlayerTransform(FTransform())
		, ExtraData(FDAB_Struct())
	{}
};
/**
 * 
 */
UCLASS()
class XHVR_API AXhAnimActorBase : public AXhActorBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XhVar|Base", meta = (ExposeOnSpawn = true))
	FAnimData AnimData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|BluprintChange")
	TArray<USkeletalMeshComponent*> SK_Comps;

public:
	UFUNCTION(BlueprintNativeEvent)
	void CreateSkeletalMeshComps();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetAnimMaxLength();
	UFUNCTION(BlueprintCallable)
	void PlayAnim();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
