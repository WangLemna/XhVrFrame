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
	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::None, EXhGrabStateEvent::E_LeftOverlap_S), EXhGrabState::LeftOverlap);
	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::None, EXhGrabStateEvent::E_RightOverlap_S), EXhGrabState::RightOverlap);
	//NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::None, EXhGrabStateEvent::E_LeftGrab_S), EXhGrabState::LeftGrabbing);
	//NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::None, EXhGrabStateEvent::E_RightGrab_S), EXhGrabState::RightGrabbing);

	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::LeftOverlap, EXhGrabStateEvent::E_LeftOverlap_E), EXhGrabState::None);
	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::LeftOverlap, EXhGrabStateEvent::E_RightOverlap_S), EXhGrabState::AllOverlap);
	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::LeftOverlap, EXhGrabStateEvent::E_LeftGrab_S), EXhGrabState::LeftGrabbing);
	//NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::LeftOverlap, EXhGrabStateEvent::E_RightGrab_S), EXhGrabState::RightGrabbing);

	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::RightOverlap, EXhGrabStateEvent::E_LeftOverlap_S), EXhGrabState::AllOverlap);
	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::RightOverlap, EXhGrabStateEvent::E_RightOverlap_E), EXhGrabState::None);
	//NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::RightOverlap, EXhGrabStateEvent::E_LeftGrab_S), EXhGrabState::LeftGrabbing);
	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::RightOverlap, EXhGrabStateEvent::E_RightGrab_S), EXhGrabState::RightGrabbing);

	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::AllOverlap, EXhGrabStateEvent::E_LeftOverlap_E), EXhGrabState::RightOverlap);
	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::AllOverlap, EXhGrabStateEvent::E_RightOverlap_E), EXhGrabState::LeftOverlap);
	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::AllOverlap, EXhGrabStateEvent::E_LeftGrab_S), EXhGrabState::LeftGrabbing);
	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::AllOverlap, EXhGrabStateEvent::E_RightGrab_S), EXhGrabState::RightGrabbing);

	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::LeftGrab, EXhGrabStateEvent::E_RightOverlap_S), EXhGrabState::LeftGrabRightOverlap);
	//NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::LeftGrab, EXhGrabStateEvent::E_RightGrab_S), EXhGrabState::RightGrabbing);
	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::LeftGrab, EXhGrabStateEvent::E_Drop), EXhGrabState::None);

	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::RightGrab, EXhGrabStateEvent::E_LeftOverlap_S), EXhGrabState::RightGrabLeftOverlap);
	//NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::RightGrab, EXhGrabStateEvent::E_LeftGrab_S), EXhGrabState::LeftGrabbing);
	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::RightGrab, EXhGrabStateEvent::E_Drop), EXhGrabState::None);

	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::LeftGrabRightOverlap, EXhGrabStateEvent::E_RightOverlap_E), EXhGrabState::LeftGrab);
	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::LeftGrabRightOverlap, EXhGrabStateEvent::E_RightGrab_S), EXhGrabState::RightGrabbing);
	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::LeftGrabRightOverlap, EXhGrabStateEvent::E_Drop), EXhGrabState::RightOverlap);

	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::RightGrabLeftOverlap, EXhGrabStateEvent::E_LeftOverlap_E), EXhGrabState::RightGrab);
	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::RightGrabLeftOverlap, EXhGrabStateEvent::E_LeftGrab_S), EXhGrabState::LeftGrabbing);
	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::RightGrabLeftOverlap, EXhGrabStateEvent::E_Drop), EXhGrabState::LeftOverlap);

	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::LeftGrabbing, EXhGrabStateEvent::E_LeftGrab_E), EXhGrabState::LeftGrab);

	NextGrabStateMap.Add(FGrabAndHandState(EXhGrabState::RightGrabbing, EXhGrabStateEvent::E_RightGrab_E), EXhGrabState::RightGrab);
}
#pragma endregion



}


void UXhGrabActorCompBase::XhRegisterGrabMeshComp(UStaticMeshComponent* InMeshComp)
{
	GrabMeshComps.AddUnique(InMeshComp);
	MeshCompsCurrentGrabState.Add(InMeshComp, EXhGrabState::None);
	MeshCompsLastGrabState.Add(InMeshComp, EXhGrabState::None);
	InMeshComp->OnComponentBeginOverlap.AddDynamic(this, &UXhGrabActorCompBase::XhNativeBeginOverlap);
	InMeshComp->OnComponentEndOverlap.AddDynamic(this, &UXhGrabActorCompBase::XhNativeEndOverlap);
}

void UXhGrabActorCompBase::XhRegisterGrabMeshComps(const TArray<UStaticMeshComponent*>& InMeshComps)
{
	for (auto& Temp : InMeshComps)
	{
		XhRegisterGrabMeshComp(Temp);
	}
}

void UXhGrabActorCompBase::XhUnregisterGrabMeshComp(UStaticMeshComponent* InMeshComp)
{
	GrabMeshComps.Remove(InMeshComp);
	MeshCompsCurrentGrabState.Remove(InMeshComp);
	MeshCompsLastGrabState.Remove(InMeshComp);
	InMeshComp->OnComponentBeginOverlap.RemoveDynamic(this, &UXhGrabActorCompBase::XhNativeBeginOverlap);
	InMeshComp->OnComponentEndOverlap.RemoveDynamic(this, &UXhGrabActorCompBase::XhNativeEndOverlap);
}

void UXhGrabActorCompBase::XhUnregisterGrabMeshComps(const TArray<UStaticMeshComponent*>& InMeshComps)
{
	for (auto& Temp : InMeshComps)
	{
		XhUnregisterGrabMeshComp(Temp);
	}
}

void UXhGrabActorCompBase::XhSetGrabMeshCompState(UStaticMeshComponent* InMeshComp, EXhGrabState InXhGrabState)
{
	if (GrabMeshComps.Contains(InMeshComp))
	{
		MeshCompsLastGrabState[InMeshComp] = MeshCompsCurrentGrabState[InMeshComp];
		MeshCompsCurrentGrabState[InMeshComp] = InXhGrabState;
	}
}

void UXhGrabActorCompBase::XhSetGrabMeshCompsState(const TArray<UStaticMeshComponent*>& InMeshComps, EXhGrabState InXhGrabState)
{
	for (auto& Temp : InMeshComps)
	{
		XhSetGrabMeshCompState(Temp, InXhGrabState);
	}
}

EXhGrabState UXhGrabActorCompBase::XhGetGrabMeshCompState(UStaticMeshComponent* InMeshComp)
{
	if (GrabMeshComps.Contains(InMeshComp))
	{
		return MeshCompsCurrentGrabState[InMeshComp];
	}
	return EXhGrabState::Max;
}

void UXhGrabActorCompBase::XhGrab(UStaticMeshComponent* InMeshComp, USceneComponent* InAttchParent, EXhGrabStateEvent InGrabStateEvent /*= EXhGrabStateEvent::Max*/, const FName& SocketName /*= NAME_None*/, float DelayAttch /*= 0*/)
{
	if (XhCanGrab(InMeshComp, InGrabStateEvent))
	{
		NextGrabeState(InMeshComp, FGrabAndHandState(MeshCompsCurrentGrabState[InMeshComp], InGrabStateEvent));
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
}

void UXhGrabActorCompBase::XhGrabEnd(UStaticMeshComponent* InMeshComp, USceneComponent* InAttchParent, const FName SocketName)
{
	InMeshComp->AttachToComponent(InAttchParent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
	EXhGrabStateEvent GrabEndEvent = EXhGrabStateEvent::Max;
	if (MeshCompsCurrentGrabState[InMeshComp] == EXhGrabState::LeftGrabbing)
	{
		GrabEndEvent = EXhGrabStateEvent::E_LeftGrab_E;
	}
	else if (MeshCompsCurrentGrabState[InMeshComp] == EXhGrabState::RightGrabbing)
	{
		GrabEndEvent = EXhGrabStateEvent::E_RightGrab_E;
	}
	NextGrabeState(InMeshComp, FGrabAndHandState(MeshCompsCurrentGrabState[InMeshComp], GrabEndEvent));
}

bool UXhGrabActorCompBase::XhCanGrab_Implementation(UStaticMeshComponent* InMeshComp, EXhGrabStateEvent InGrabStateEvent/* = EXhGrabStateEvent::Max*/)
{
	if (InGrabStateEvent == EXhGrabStateEvent::Max)
	{
		EXhGrabState LeftGrab = GetNextGrabeState(FGrabAndHandState(MeshCompsCurrentGrabState[InMeshComp], EXhGrabStateEvent::E_LeftGrab_S));
		EXhGrabState RightGrab = GetNextGrabeState(FGrabAndHandState(MeshCompsCurrentGrabState[InMeshComp], EXhGrabStateEvent::E_RightGrab_S));
		return LeftGrab == EXhGrabState::LeftGrabbing || RightGrab == EXhGrabState::RightGrabbing;
	}
	else
	{
		EXhGrabState Grab = GetNextGrabeState(FGrabAndHandState(MeshCompsCurrentGrabState[InMeshComp], InGrabStateEvent));
		return Grab == EXhGrabState::LeftGrabbing || Grab == EXhGrabState::RightGrabbing;
	}
}

void UXhGrabActorCompBase::XhNativeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(OverlappedComponent))
	{
		if (GrabMeshComps.Contains(SM))
		{
			EXhGrabStateEvent XhGrabStateEvent = EXhGrabStateEvent::None;
			if (LeftGrabCollisionComps.Contains(OtherComp))
			{
				XhGrabStateEvent = EXhGrabStateEvent::E_LeftOverlap_S;
			}
			if (RightGrabCollisionComps.Contains(OtherComp))
			{
				XhGrabStateEvent = EXhGrabStateEvent::E_RightOverlap_S;
			}
			NextGrabeState(SM, FGrabAndHandState(*MeshCompsCurrentGrabState.Find(SM), XhGrabStateEvent));
		}
	}
}

void UXhGrabActorCompBase::XhNativeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(OverlappedComponent))
	{
		if (GrabMeshComps.Contains(SM))
		{
			EXhGrabStateEvent XhGrabStateEvent = EXhGrabStateEvent::None;
			if (LeftGrabCollisionComps.Contains(OtherComp))
			{
				XhGrabStateEvent = EXhGrabStateEvent::E_LeftOverlap_E;
			}
			if (RightGrabCollisionComps.Contains(OtherComp))
			{
				XhGrabStateEvent = EXhGrabStateEvent::E_RightOverlap_E;
			}
			NextGrabeState(SM, FGrabAndHandState(*MeshCompsCurrentGrabState.Find(SM), XhGrabStateEvent));
		}
	}
}

EXhGrabState UXhGrabActorCompBase::NextGrabeState(UStaticMeshComponent* InMeshComp, FGrabAndHandState InGrabAndHandState)
{
	if (NextGrabStateMap.Contains(InGrabAndHandState))
	{
		MeshCompsLastGrabState[InMeshComp] = MeshCompsCurrentGrabState[InMeshComp];
		MeshCompsCurrentGrabState[InMeshComp] = NextGrabStateMap[InGrabAndHandState];
	}
	return MeshCompsCurrentGrabState[InMeshComp];
}

EXhGrabState UXhGrabActorCompBase::GetNextGrabeState(FGrabAndHandState InGrabAndHandState)
{
	if (NextGrabStateMap.Contains(InGrabAndHandState))
	{
		return *NextGrabStateMap.Find(InGrabAndHandState);
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

