// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Actor/XhOperateActorBase.h"
#include "Base/Actor/XhActorBase.h"
#include "Base/GameBase/XhCharacter.h"

AXhOperateActorBase::AXhOperateActorBase()
{
	//bCanOpera = true;
}




void AXhOperateActorBase::OculusA_Implementation(EButtonEvent InButtonEvent)
{
}

void AXhOperateActorBase::OculusB_Implementation(EButtonEvent InButtonEvent)
{
}

void AXhOperateActorBase::OculusX_Implementation(EButtonEvent InButtonEvent)
{
}

void AXhOperateActorBase::OculusY_Implementation(EButtonEvent InButtonEvent)
{
}

void AXhOperateActorBase::OculusJoystickL_Implementation(EButtonEvent InButtonEvent)
{
}

void AXhOperateActorBase::OculusJoystickR_Implementation(EButtonEvent InButtonEvent)
{
}

void AXhOperateActorBase::OculusGripL_Implementation(EButtonEvent InButtonEvent)
{
}

void AXhOperateActorBase::OculusGripR_Implementation(EButtonEvent InButtonEvent)
{
}

void AXhOperateActorBase::OculusTriggerL_Implementation(EButtonEvent InButtonEvent)
{
}

void AXhOperateActorBase::OculusTriggerR_Implementation(EButtonEvent InButtonEvent)
{
}


void AXhOperateActorBase::BeginPlay()
{
	XH_BP_EXEC_B(XhBegin);
	Super::BeginPlay();
	XH_BP_EXEC_E(XhBegin);
}


void AXhOperateActorBase::XhNativeInit()
{
	Super::XhNativeInit();
}

void AXhOperateActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
