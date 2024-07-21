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
}


void UXhGrabActorCompBase::XhRegisterGrabMeshComp(UStaticMeshComponent* InMeshComp)
{
	GrabMeshComps.AddUnique(InMeshComp);
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

void UXhGrabActorCompBase::XhNativeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (XhCharacter && OtherActor == XhCharacter)
	{
		if (UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(OverlappedComponent))
		{
			if (GrabMeshComps.Contains(SM))
			{
				EXhGrabState XhGrabState = EXhGrabState::None;
				if (OtherComp == Cast<UStaticMeshComponent>(XhCharacter->GetGrabCollision(EXhHand::L_Hand)))
				{
					XhGrabState = XhGrabState == EXhGrabState::RightCatch ? EXhGrabState::AllCatch : EXhGrabState::LeftCatch;
				}
				if (OtherComp == Cast<UStaticMeshComponent>(XhCharacter->GetGrabCollision(EXhHand::R_Hand)))
				{
					XhGrabState = XhGrabState == EXhGrabState::LeftCatch ? EXhGrabState::AllCatch : EXhGrabState::RightCatch;
				}
				
				MeshCompsGrabState.Add(SM, EXhGrabState::LeftCatch);
			}

		}
	}
}

void UXhGrabActorCompBase::XhNativeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

EXhGrabState UXhGrabActorCompBase::NextGrabeState(UStaticMeshComponent* InMeshComp, EXhGrabState InGrabState)
{
	return EXhGrabState::None;
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

