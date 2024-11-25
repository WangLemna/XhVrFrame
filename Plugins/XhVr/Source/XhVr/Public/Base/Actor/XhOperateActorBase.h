// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/IXhOculusEvent.h"
#include "Base/Actor/XhActorBase.h"
#include "XhOperateActorBase.generated.h"

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
	// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Base")
	int32 Process;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Debug")
	TArray<FOculusEventMode> DebugOperaEvent;
	//~ Begin IXhOculusEvent Interface.
public:
	void OculusA_Implementation(EButtonEvent InButtonEvent);
	void OculusB_Implementation(EButtonEvent InButtonEvent);
	void OculusX_Implementation(EButtonEvent InButtonEvent);
	void OculusY_Implementation(EButtonEvent InButtonEvent);
	void OculusJoystickL_Implementation(EButtonEvent InButtonEvent);
	void OculusJoystickR_Implementation(EButtonEvent InButtonEvent);
	void OculusGripL_Implementation(EButtonEvent InButtonEvent);
	void OculusGripR_Implementation(EButtonEvent InButtonEvent);
	void OculusTriggerL_Implementation(EButtonEvent InButtonEvent);
	void OculusTriggerR_Implementation(EButtonEvent InButtonEvent);
	//~ End IXhOculusEvent Interface.

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void XhNativeInit() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
