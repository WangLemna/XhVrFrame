// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Actor/XhOperateActorBase.h"
#include "Base/Actor/XhActorBase.h"

AXhOperateActorBase::AXhOperateActorBase()
{

}

void AXhOperateActorBase::BeginPlay()
{
	XH_BP_EXEC_B(XhBegin);
	Super::BeginPlay();
	XH_BP_EXEC_E(XhBegin);
}

void AXhOperateActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
