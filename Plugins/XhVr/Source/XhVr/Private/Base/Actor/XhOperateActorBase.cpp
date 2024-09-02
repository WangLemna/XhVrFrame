// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Actor/XhOperateActorBase.h"
#include "Base/Actor/XhActorBase.h"
#include "Base/Grab/XhGrabActorCompBase.h"
#include "Base/GameBase/XhCharacter.h"
#include "Base/ActorComponent/XhGrabMeshComponent.h"

AXhOperateActorBase::AXhOperateActorBase()
{
	bCanOpera = true;
	GrabActorCompBase = CreateDefaultSubobject<UXhGrabActorCompBase>(TEXT("GrabActorCompBase"));
	GrabActorCompBase->bAutoActivate = true;
	bAutoInitGrab = true;
	GrabComp = nullptr;
}


#define XH_DELEGATE_EVENT(x) \
if (TArray<UXhGrabMeshComponent*>* TempPtr = XhGrabMeshCompEventMap.Find(FOculusEventMode((x), InButtonEvent)))\
{\
	for (UXhGrabMeshComponent* Temp : *TempPtr)\
	{\
		Temp->XhDelegateEvents(FOculusEventMode((x), InButtonEvent), GrabComp);\
	}\
}


void AXhOperateActorBase::OculusA_Implementation(EButtonEvent InButtonEvent)
{
	XH_DELEGATE_EVENT(EOculusEvent::OculusA);
}

void AXhOperateActorBase::OculusB_Implementation(EButtonEvent InButtonEvent)
{
	XH_DELEGATE_EVENT(EOculusEvent::OculusB);
}

void AXhOperateActorBase::OculusX_Implementation(EButtonEvent InButtonEvent)
{
	XH_DELEGATE_EVENT(EOculusEvent::OculusX);
}

void AXhOperateActorBase::OculusY_Implementation(EButtonEvent InButtonEvent)
{
	XH_DELEGATE_EVENT(EOculusEvent::OculusY);
}

void AXhOperateActorBase::OculusJoystickL_Implementation(EButtonEvent InButtonEvent)
{
	XH_DELEGATE_EVENT(EOculusEvent::OculusJoystickL);
}

void AXhOperateActorBase::OculusJoystickR_Implementation(EButtonEvent InButtonEvent)
{
	XH_DELEGATE_EVENT(EOculusEvent::OculusJoystickR);
}

void AXhOperateActorBase::OculusGripL_Implementation(EButtonEvent InButtonEvent)
{
	XH_DELEGATE_EVENT(EOculusEvent::OculusGripL);
}

void AXhOperateActorBase::OculusGripR_Implementation(EButtonEvent InButtonEvent)
{
	XH_DELEGATE_EVENT(EOculusEvent::OculusGripR);
}

void AXhOperateActorBase::OculusTriggerL_Implementation(EButtonEvent InButtonEvent)
{
	XH_DELEGATE_EVENT(EOculusEvent::OculusTriggerL);
}

void AXhOperateActorBase::OculusTriggerR_Implementation(EButtonEvent InButtonEvent)
{
	XH_DELEGATE_EVENT(EOculusEvent::OculusTriggerR);
// 	if (TArray<UXhGrabMeshComponent*>* TempPtr = XhGrabMeshCompEventMap.Find(FOculusEventMode(EOculusEvent::OculusTriggerR, InButtonEvent)))
// 	{
// 		for (UXhGrabMeshComponent* Temp : *TempPtr)
// 		{
// 			 Temp->XhDelegateEvents(FOculusEventMode(EOculusEvent::OculusTriggerR, InButtonEvent), GrabComp);
// 		}
// 	}
}
#undef XH_DELEGATE_EVENT

void AXhOperateActorBase::XhRegisterGrabMeshComps(TArray<UStaticMeshComponent*> InXhGrabMeshComps)
{
	for (auto& Temp : InXhGrabMeshComps)
	{
		if (UXhGrabMeshComponent* GM = Cast<UXhGrabMeshComponent>(Temp))
		{
			XhRegisterGrabMeshComp(GM);
		}
	}
}

void AXhOperateActorBase::XhRegisterGrabMeshComp(UXhGrabMeshComponent* InXhGrabMeshComp)
{
	for (auto& Temp : InXhGrabMeshComp->GetOculusEvents())
	{
		if (XhGrabMeshCompEventMap.Contains(Temp))
		{
			XhGrabMeshCompEventMap.Find(Temp)->Add(InXhGrabMeshComp);
		}
		else
		{
			XhGrabMeshCompEventMap.Add(Temp, { InXhGrabMeshComp });
		}
	}
}

void AXhOperateActorBase::XhGrab(UStaticMeshComponent* InMeshComp, USceneComponent* InAttchParent, EXhHand InHand /*= EXhHand::Max*/, const FName SocketName /*= NAME_None*/, float DelayAttch /*= 0*/)
{
	if (GrabComp)
	{
		GrabComp->XhGrab(InMeshComp, InAttchParent, InHand, SocketName, DelayAttch);
	}
	else
	{
		UXhTool::WriteLog(this, TEXT("XhGrab:GrabComp无效！"));
	}
}

void AXhOperateActorBase::XhDrop(UStaticMeshComponent* InMeshComp)
{
	if (GrabComp)
	{
		GrabComp->XhDrop(InMeshComp);
	}
	else
	{
		UXhTool::WriteLog(this, TEXT("XhGrab:GrabComp无效！"));
	}
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
	if (bCanOpera && XhCharacter && GrabComp)//GrabActorCompBase
	{
		GrabComp->LeftGrabCollisionComps.Add((UPrimitiveComponent*)XhCharacter->GetGrabCollision(EXhHand::Left));
		GrabComp->RightGrabCollisionComps.Add((UPrimitiveComponent*)XhCharacter->GetGrabCollision(EXhHand::Right));
		TArray<UStaticMeshComponent*> OutStaticMeshes;
		GetComponents(UStaticMeshComponent::StaticClass(), OutStaticMeshes);
		GrabComp->XhRegisterComps(OutStaticMeshes);
		XhRegisterGrabMeshComps(OutStaticMeshes);
		//GrabComp = GrabActorCompBase;
	}
	else
	{
		UXhTool::WriteLog(this, TEXT("InitGrab:初始化抓取失败！"));
	}
}

void AXhOperateActorBase::XhNativeInit()
{
	Super::XhNativeInit();
	GrabComp = GetComponentByClass<UXhGrabActorCompBase>();
	if (GrabComp)
	{
		GrabComp = GrabComp->IsActive() ? GrabComp : nullptr;
	}
}

void AXhOperateActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
