// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/ActorComponent/XhGrabMeshComponent.h"
#include "Base/Grab/XhGrabActorCompBase.h"

UXhGrabMeshComponent::UXhGrabMeshComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bAutoXhRegister = true;
}

void UXhGrabMeshComponent::XhDelegateEvents(FOculusEventMode InOculusEventMode, UXhGrabActorCompBase* GrabComp)
{
	TArray<EXhGrabMeshCompnentEventType> Arr = *DelegateEventsMap.Find(InOculusEventMode);
	for (auto Temp : Arr)
	{
		switch (Temp)
		{
		case EXhGrabMeshCompnentEventType::Grab:
		{
			if (IsValid(this) && GrabComp->XhCanGrab(this))
			{
				GrabComp->XhGrab(this, AttchParent, InOculusEventMode.GetHand(), SocketName, DelayAttach);
				OnComponentGrab.Broadcast(AttchParent, DelayAttach);
			}
		}
			break;
		case EXhGrabMeshCompnentEventType::Drop:
		{
			if (IsValid(this) && GrabComp->XhCanDrop(this))
			{
				GrabComp->XhDrop(this);
				OnComponentDrop.Broadcast(AttchParent);
			}
		}
			break;
		default:
			break;
		}
	}
}

void UXhGrabMeshComponent::XhNativeInit()
{
	if (bAutoXhRegister)
	{
		if (GrabOculusEventMode.IsValidData())
		{
			if (DelegateEventsMap.Contains(GrabOculusEventMode))
			{
				DelegateEventsMap.Find(GrabOculusEventMode)->Add(EXhGrabMeshCompnentEventType::Grab);
			}
			else
			{
				DelegateEventsMap.Add(GrabOculusEventMode, { EXhGrabMeshCompnentEventType::Grab });
			}
		}
		if (DropOculusEventMode.IsValidData())
		{

			if (DelegateEventsMap.Contains(GrabOculusEventMode))
			{
				DelegateEventsMap.Find(GrabOculusEventMode)->Add(EXhGrabMeshCompnentEventType::Drop);
			}
			else
			{
				DelegateEventsMap.Add(GrabOculusEventMode, { EXhGrabMeshCompnentEventType::Drop });
			}
		}
	}
}

TArray<FOculusEventMode> UXhGrabMeshComponent::GetOculusEvents()
{
	TArray<FOculusEventMode> Results;
	DelegateEventsMap.GetKeys(Results);
	return Results;
}

void UXhGrabMeshComponent::BeginPlay()
{
	Super::BeginPlay();
	XhNativeInit();
}


// if (IsValid(this))
// {
// 	OnComponentBeginOverlap.Broadcast(this, OtherActor, OtherComp, OtherOverlap.GetBodyIndex(), OtherOverlap.bFromSweep, OtherOverlap.OverlapInfo);
// }

