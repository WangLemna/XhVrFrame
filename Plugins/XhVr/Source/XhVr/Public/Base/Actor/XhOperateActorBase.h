// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/IXhOculusEvent.h"
#include "XhOperateActorBase.generated.h"

class UXhGrabActorCompBase;

/**
 * 
 */
UCLASS()
class XHVR_API AXhOperateActorBase : public AXhActorBase, public IXhOculusEvent
{
	GENERATED_BODY()
public:
	AXhOperateActorBase();
public:
	//XhRegisterGrabMeshComps()
	//LeftGrabCollisionComps  RightGrabCollisionComps
	UPROPERTY(Category = "XhOperateActorBase", VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UXhGrabActorCompBase> GrabActorCompBase;


public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XhVar|Settings")
	bool bAutoInitGrab;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void InitGrab();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
