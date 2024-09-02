// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Grab/XhGrabActorCompBase.h"


// Sets default values for this component's properties
UXhGrabActorCompBase::UXhGrabActorCompBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
#pragma region NextStateMapInit
{
	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::None, EXhGrabEvent::E_LeftOverlap_S), EXhGrabState::LeftOverlap);
	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::None, EXhGrabEvent::E_RightOverlap_S), EXhGrabState::RightOverlap);
	//NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::None, EXhGrabStateEvent::E_LeftGrab_S), EXhGrabState::LeftGrabbing);
	//NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::None, EXhGrabStateEvent::E_RightGrab_S), EXhGrabState::RightGrabbing);

	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::LeftOverlap, EXhGrabEvent::E_LeftOverlap_E), EXhGrabState::None);
	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::LeftOverlap, EXhGrabEvent::E_RightOverlap_S), EXhGrabState::AllOverlap);
	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::LeftOverlap, EXhGrabEvent::E_LeftGrab_S), EXhGrabState::LeftGrabbing);
	//NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::LeftOverlap, EXhGrabStateEvent::E_RightGrab_S), EXhGrabState::RightGrabbing);

	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::RightOverlap, EXhGrabEvent::E_LeftOverlap_S), EXhGrabState::AllOverlap);
	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::RightOverlap, EXhGrabEvent::E_RightOverlap_E), EXhGrabState::None);
	//NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::RightOverlap, EXhGrabStateEvent::E_LeftGrab_S), EXhGrabState::LeftGrabbing);
	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::RightOverlap, EXhGrabEvent::E_RightGrab_S), EXhGrabState::RightGrabbing);

	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::AllOverlap, EXhGrabEvent::E_LeftOverlap_E), EXhGrabState::RightOverlap);
	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::AllOverlap, EXhGrabEvent::E_RightOverlap_E), EXhGrabState::LeftOverlap);
	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::AllOverlap, EXhGrabEvent::E_LeftGrab_S), EXhGrabState::LeftGrabbing);
	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::AllOverlap, EXhGrabEvent::E_RightGrab_S), EXhGrabState::RightGrabbing);

	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::LeftGrab, EXhGrabEvent::E_RightOverlap_S), EXhGrabState::LeftGrabRightOverlap);
	//NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::LeftGrab, EXhGrabStateEvent::E_RightGrab_S), EXhGrabState::RightGrabbing);
	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::LeftGrab, EXhGrabEvent::E_Drop), EXhGrabState::None);

	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::RightGrab, EXhGrabEvent::E_LeftOverlap_S), EXhGrabState::RightGrabLeftOverlap);
	//NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::RightGrab, EXhGrabStateEvent::E_LeftGrab_S), EXhGrabState::LeftGrabbing);
	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::RightGrab, EXhGrabEvent::E_Drop), EXhGrabState::None);

	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::LeftGrabRightOverlap, EXhGrabEvent::E_RightOverlap_E), EXhGrabState::LeftGrab);
	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::LeftGrabRightOverlap, EXhGrabEvent::E_RightGrab_S), EXhGrabState::RightGrabbing);
	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::LeftGrabRightOverlap, EXhGrabEvent::E_Drop), EXhGrabState::RightOverlap);

	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::RightGrabLeftOverlap, EXhGrabEvent::E_LeftOverlap_E), EXhGrabState::RightGrab);
	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::RightGrabLeftOverlap, EXhGrabEvent::E_LeftGrab_S), EXhGrabState::LeftGrabbing);
	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::RightGrabLeftOverlap, EXhGrabEvent::E_Drop), EXhGrabState::LeftOverlap);

	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::LeftGrabbing, EXhGrabEvent::E_LeftGrab_E), EXhGrabState::LeftGrab);

	NextGrabStateMap.Add(FGrabAndGrabEvent(EXhGrabState::RightGrabbing, EXhGrabEvent::E_RightGrab_E), EXhGrabState::RightGrab);
}
#pragma endregion



}

void UXhGrabActorCompBase::XhRegisterComp(UStaticMeshComponent* InMeshComp)
{
	Comps.AddUnique(InMeshComp);
	CompsCurrentGrabState.Add(InMeshComp, EXhGrabState::None);
	CompsLastGrabState.Add(InMeshComp, EXhGrabState::None);
	InMeshComp->OnComponentBeginOverlap.AddDynamic(this, &UXhGrabActorCompBase::XhNativeBeginOverlap);
	InMeshComp->OnComponentEndOverlap.AddDynamic(this, &UXhGrabActorCompBase::XhNativeEndOverlap);
}

void UXhGrabActorCompBase::XhRegisterComps(const TArray<UStaticMeshComponent*>& InMeshComps)
{
	for (auto& Temp : InMeshComps)
	{
		XhRegisterComp(Temp);
	}
}

void UXhGrabActorCompBase::XhUnregisterComp(UStaticMeshComponent* InMeshComp)
{
	Comps.Remove(InMeshComp);
	CompsCurrentGrabState.Remove(InMeshComp);
	CompsLastGrabState.Remove(InMeshComp);
	InMeshComp->OnComponentBeginOverlap.RemoveDynamic(this, &UXhGrabActorCompBase::XhNativeBeginOverlap);
	InMeshComp->OnComponentEndOverlap.RemoveDynamic(this, &UXhGrabActorCompBase::XhNativeEndOverlap);
}

void UXhGrabActorCompBase::XhUnregisterComps(const TArray<UStaticMeshComponent*>& InMeshComps)
{
	for (auto& Temp : InMeshComps)
	{
		XhUnregisterComp(Temp);
	}
}

void UXhGrabActorCompBase::XhSetCompState(UStaticMeshComponent* InMeshComp, EXhGrabState InXhGrabState)
{
	if (Comps.Contains(InMeshComp))
	{
		CompsLastGrabState[InMeshComp] = CompsCurrentGrabState[InMeshComp];
		CompsCurrentGrabState[InMeshComp] = InXhGrabState;
	}
}

void UXhGrabActorCompBase::XhSetCompsState(const TArray<UStaticMeshComponent*>& InMeshComps, EXhGrabState InXhGrabState)
{
	for (auto& Temp : InMeshComps)
	{
		XhSetCompState(Temp, InXhGrabState);
	}
}

EXhGrabState UXhGrabActorCompBase::XhGetCompState(UStaticMeshComponent* InMeshComp)
{
	if (Comps.Contains(InMeshComp))
	{
		return CompsCurrentGrabState[InMeshComp];
	}
	return EXhGrabState::Max;
}

EXhGrabState UXhGrabActorCompBase::XhGetCompLastState(UStaticMeshComponent* InMeshComp)
{
	if (Comps.Contains(InMeshComp))
	{
		return CompsLastGrabState[InMeshComp];
	}
	return EXhGrabState::Max;
}

bool UXhGrabActorCompBase::XhCanGrab_Implementation(UStaticMeshComponent* InMeshComp, EXhGrabEvent InGrabStateEvent/* = EXhGrabStateEvent::Max*/)
{
	if (InGrabStateEvent == EXhGrabEvent::Max)
	{
		EXhGrabState LeftGrab = GetNextGrabeState(FGrabAndGrabEvent(XhGetCompState(InMeshComp), EXhGrabEvent::E_LeftGrab_S));
		EXhGrabState RightGrab = GetNextGrabeState(FGrabAndGrabEvent(XhGetCompState(InMeshComp), EXhGrabEvent::E_RightGrab_S));
		return LeftGrab == EXhGrabState::LeftGrabbing || RightGrab == EXhGrabState::RightGrabbing;
	}
	else
	{
		EXhGrabState Grab = GetNextGrabeState(FGrabAndGrabEvent(XhGetCompState(InMeshComp), InGrabStateEvent));
		return Grab == EXhGrabState::LeftGrabbing || Grab == EXhGrabState::RightGrabbing;
	}
}

void UXhGrabActorCompBase::XhGrab(UStaticMeshComponent* InMeshComp, USceneComponent* InAttchParent, EXhHand InHand /*= EXhHand::Max*/, const FName SocketName /*= NAME_None*/, float DelayAttch /*= 0*/)
{
	EXhGrabEvent GrabStateEvent = EXhGrabEvent::Max;
	switch (InHand)
	{
	case EXhHand::None:
		break;
	case EXhHand::Left:
		GrabStateEvent = EXhGrabEvent::E_LeftGrab_S;
		break;
	case EXhHand::Right:
		GrabStateEvent = EXhGrabEvent::E_RightGrab_S;
		break;
	case EXhHand::Max:
		break;
	default:
		break;
	}
	if (XhCanGrab(InMeshComp, GrabStateEvent))
	{
		NextGrabeState(InMeshComp, FGrabAndGrabEvent(XhGetCompState(InMeshComp), GrabStateEvent));
		if (DelayAttch <= 0)
		{
			XhGrabEnd(InMeshComp, InAttchParent, SocketName);
		}
		else
		{
			FTimerHandle TimerHandle;
			FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UXhGrabActorCompBase::XhGrabEnd, InMeshComp, InAttchParent, SocketName);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, DelayAttch, false);
		}
	}
	else
	{
		FString StringLog = FString::Printf(TEXT("无法抓取，【%s】当前状态为【%s】，发生的事件为【%s】！"), *InMeshComp->GetName(), *EnumToString(XhGetCompState(InMeshComp)), *EnumToString(GrabStateEvent));
		UXhTool::PrintLog(StringLog);
	}
}

bool UXhGrabActorCompBase::XhCanDrop_Implementation(UStaticMeshComponent* InMeshComp)
{
	return GetNextGrabeState(FGrabAndGrabEvent(XhGetCompState(InMeshComp), EXhGrabEvent::E_Drop)) != EXhGrabState::Max;
}

void UXhGrabActorCompBase::XhDrop(UStaticMeshComponent* InMeshComp)
{
	if (XhCanDrop(InMeshComp))
	{
		NextGrabeState(InMeshComp, FGrabAndGrabEvent(XhGetCompState(InMeshComp), EXhGrabEvent::E_Drop));
		InMeshComp->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
	else
	{
		FString StringLog = FString::Printf(TEXT("无法扔下，【%s】当前状态为【%s】！"), *InMeshComp->GetName(), *EnumToString(XhGetCompState(InMeshComp)));
		UXhTool::PrintLog(StringLog);
	}
}

void UXhGrabActorCompBase::XhGrabEnd(UStaticMeshComponent* InMeshComp, USceneComponent* InAttchParent, const FName SocketName)
{
	InMeshComp->AttachToComponent(InAttchParent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
	EXhGrabEvent GrabEndEvent = EXhGrabEvent::Max;
	if (XhGetCompState(InMeshComp) == EXhGrabState::LeftGrabbing)
	{
		GrabEndEvent = EXhGrabEvent::E_LeftGrab_E;
	}
	else if (XhGetCompState(InMeshComp) == EXhGrabState::RightGrabbing)
	{
		GrabEndEvent = EXhGrabEvent::E_RightGrab_E;
	}
	NextGrabeState(InMeshComp, FGrabAndGrabEvent(XhGetCompState(InMeshComp), GrabEndEvent));
	if (InAttchParent)
	{
		FString Log = FString::Printf(TEXT("GrabEnd:AttchParent为为空！但是%s的状态已经改变为【%s】"), *InMeshComp->GetName(), *EnumToString(XhGetCompState(InMeshComp)));
	}
}

void UXhGrabActorCompBase::XhNativeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(OverlappedComponent))
	{
		if (Comps.Contains(SM))
		{
			EXhGrabEvent XhGrabStateEvent = EXhGrabEvent::None;
			if (LeftGrabCollisionComps.Contains(OtherComp))
			{
				XhGrabStateEvent = EXhGrabEvent::E_LeftOverlap_S;
			}
			if (RightGrabCollisionComps.Contains(OtherComp))
			{
				XhGrabStateEvent = EXhGrabEvent::E_RightOverlap_S;
			}
			NextGrabeState(SM, FGrabAndGrabEvent(XhGetCompState(SM), XhGrabStateEvent));
		}
	}
}

void UXhGrabActorCompBase::XhNativeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(OverlappedComponent))
	{
		if (Comps.Contains(SM))
		{
			EXhGrabEvent XhGrabStateEvent = EXhGrabEvent::None;
			if (LeftGrabCollisionComps.Contains(OtherComp))
			{
				XhGrabStateEvent = EXhGrabEvent::E_LeftOverlap_E;
			}
			if (RightGrabCollisionComps.Contains(OtherComp))
			{
				XhGrabStateEvent = EXhGrabEvent::E_RightOverlap_E;
			}
			NextGrabeState(SM, FGrabAndGrabEvent(XhGetCompState(SM), XhGrabStateEvent));
		}
	}
}

EXhGrabState UXhGrabActorCompBase::NextGrabeState(UStaticMeshComponent* InMeshComp, FGrabAndGrabEvent InGrabAndHandState)
{
	if (Comps.Contains(InMeshComp) && NextGrabStateMap.Contains(InGrabAndHandState))
	{
		CompsLastGrabState[InMeshComp] = CompsCurrentGrabState[InMeshComp];
		CompsCurrentGrabState[InMeshComp] = NextGrabStateMap[InGrabAndHandState];
	}
	return XhGetCompState(InMeshComp);
}

EXhGrabState UXhGrabActorCompBase::GetNextGrabeState(FGrabAndGrabEvent InGrabAndHandState)
{
	if (NextGrabStateMap.Contains(InGrabAndHandState))
	{
		return NextGrabStateMap[InGrabAndHandState];
	}
	return EXhGrabState::Max;
}

// Called when the game starts
void UXhGrabActorCompBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//XhRegisterGrabMeshComps(const TArray<UStaticMeshComponent*>& InMeshComps)
	//LeftGrabCollisionComps  RightGrabCollisionComps
}


// Called every frame
void UXhGrabActorCompBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

