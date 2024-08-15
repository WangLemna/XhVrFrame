// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Actor/XhOperateActorBase.h"
#include "Base/Actor/XhActorBase.h"
#include "Base/Grab/XhGrabActorCompBase.h"
#include "Base/GameBase/XhCharacter.h"

AXhOperateActorBase::AXhOperateActorBase()
{
	bCanOpera = true;
	GrabActorCompBase = CreateDefaultSubobject<UXhGrabActorCompBase>(TEXT("GrabActorCompBase"));
	bAutoInitGrab = true;
}

void AXhOperateActorBase::BeginPlay()
{
	XH_BP_EXEC_B(XhBegin);
	Super::BeginPlay();
	if (bAutoInitGrab)
	{
		InitGrab();
	}
	XH_BP_EXEC_E(XhBegin);
}

void AXhOperateActorBase::InitGrab()
{
	if (bCanOpera && XhCharacter && GrabActorCompBase)
	{
		GrabActorCompBase->LeftGrabCollisionComps.Add((UPrimitiveComponent*)XhCharacter->GetGrabCollision(EXhHand::L_Hand));
		GrabActorCompBase->RightGrabCollisionComps.Add((UPrimitiveComponent*)XhCharacter->GetGrabCollision(EXhHand::R_Hand));
		TArray<UStaticMeshComponent*> OutStaticMeshes;
		GetComponents(UStaticMeshComponent::StaticClass(), OutStaticMeshes);
		GrabActorCompBase->XhRegisterGrabMeshComps(OutStaticMeshes);
	}
	else
	{
		UXhTool::WriteLog(this, TEXT("InitGrab:初始化抓取失败！"));
	}
}

void AXhOperateActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
