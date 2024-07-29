// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Grab/XhGrabActorCompBase.h"
#include "Base/GameBase/XhCharacter.h"
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

void UXhGrabActorCompBase::XhGrab_Implementation(UStaticMeshComponent* InMeshComp, USceneComponent* AttchParent)
{
	/*switch (InXhHand)
	{
	case EXhHand::None:
		break;
	case EXhHand::L_Hand:
		break;
	case EXhHand::R_Hand:
		break;
	case EXhHand::Max:
		break;
	default:
		break;
	}*/
}

bool UXhGrabActorCompBase::XhCanGrab_Implementation(UStaticMeshComponent* InMeshComp)
{
	EXhGrabState LeftGrab = GetNextGrabeState(FGrabAndHandState(MeshCompsCurrentGrabState[InMeshComp], EXhGrabStateEvent::E_LeftGrab_S));
	EXhGrabState RightGrab = GetNextGrabeState(FGrabAndHandState(MeshCompsCurrentGrabState[InMeshComp], EXhGrabStateEvent::E_RightGrab_S));
	return LeftGrab == EXhGrabState::LeftGrabbing || RightGrab == EXhGrabState::RightGrabbing;
}

void UXhGrabActorCompBase::XhNativeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (XhCharacter && OtherActor == XhCharacter)
	{
		if (UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(OverlappedComponent))
		{
			if (GrabMeshComps.Contains(SM))
			{
				EXhGrabStateEvent XhGrabStateEvent = EXhGrabStateEvent::None;
				if (OtherComp == Cast<UStaticMeshComponent>(XhCharacter->GetGrabCollision(EXhHand::L_Hand)))
				{
					XhGrabStateEvent = EXhGrabStateEvent::E_LeftOverlap_S;
				}
				if (OtherComp == Cast<UStaticMeshComponent>(XhCharacter->GetGrabCollision(EXhHand::R_Hand)))
				{
					XhGrabStateEvent = EXhGrabStateEvent::E_RightOverlap_S;
				}
				NextGrabeState(SM, FGrabAndHandState(*MeshCompsCurrentGrabState.Find(SM), XhGrabStateEvent));
			}
		}
	}
}

void UXhGrabActorCompBase::XhNativeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (XhCharacter && OtherActor == XhCharacter)
	{
		if (UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(OverlappedComponent))
		{
			if (GrabMeshComps.Contains(SM))
			{
				EXhGrabStateEvent XhGrabStateEvent = EXhGrabStateEvent::None;
				if (OtherComp == Cast<UStaticMeshComponent>(XhCharacter->GetGrabCollision(EXhHand::L_Hand)))
				{
					XhGrabStateEvent = EXhGrabStateEvent::E_LeftOverlap_E;
				}
				if (OtherComp == Cast<UStaticMeshComponent>(XhCharacter->GetGrabCollision(EXhHand::R_Hand)))
				{
					XhGrabStateEvent = EXhGrabStateEvent::E_RightOverlap_E;
				}
				NextGrabeState(SM, FGrabAndHandState(*MeshCompsCurrentGrabState.Find(SM), XhGrabStateEvent));
			}
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
	
}


// Called every frame
void UXhGrabActorCompBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

