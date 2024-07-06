// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBase/XhWalkActorBase.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SplineMeshComponent.h"
#include "GameBase/XhWalkActorCompBase.h"



// Sets default values
AXhWalkActorBase::AXhWalkActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WalkRoot = CreateDefaultSubobject<USceneComponent>(TEXT("WalkRoot"));
	TraceSpline = CreateDefaultSubobject<USplineComponent>(TEXT("TraceSpline"));
	EndLocation = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EndLocation"));
	WalkArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("WalkArrow"));
	WalkActorCompBase = CreateDefaultSubobject<UXhWalkActorCompBase>(TEXT("WalkActorCompBase"));

	RootComponent = WalkRoot;
	TraceSpline->SetupAttachment(WalkRoot);
	EndLocation->SetupAttachment(TraceSpline);
	WalkArrow->SetupAttachment(TraceSpline);

	//bIsDot = true;
	//SimFrequency = 25.0f;
	//WalkDistance = 500.0f;
	//FadeInDuration = 0.2f;
	//FadeOutDuration = 0.2f;
	//DrawDebugType = EDrawDebugTrace::ForOneFrame;
	//FadeColor = FLinearColor::Black;
	//InitailLocationZ = 0;

	//if (WalkActorCompBase)
	//{
	//	WalkActorCompBase->bIsDot = bIsDot;
	//	WalkActorCompBase->SimFrequency = SimFrequency;
	//	WalkActorCompBase->WalkDistance = WalkDistance;
	//	WalkActorCompBase->FadeInDuration = FadeInDuration;
	//	WalkActorCompBase->FadeOutDuration = FadeOutDuration;
	//	WalkActorCompBase->DrawDebugType = DrawDebugType;
	//	WalkActorCompBase->FadeColor = FadeColor;
	//	WalkActorCompBase->InitailLocationZ = InitailLocationZ;
	//	WalkActorCompBase->SplineMeshStyle = SplineMeshStyle;
	//}




}

void AXhWalkActorBase::XhStartWalk()
{
	if (WalkActorCompBase)
	{
		WalkActorCompBase->XhStartWalk();
	}
}

void AXhWalkActorBase::XhEndWalk()
{
	if (WalkActorCompBase)
	{
		WalkActorCompBase->XhEndWalk();
	}
}

void AXhWalkActorBase::XhSetWalker(AActor* InWalker)
{
	if (WalkActorCompBase)
	{
		WalkActorCompBase->XhRegisterWalkActor(InWalker, TraceSpline, WalkArrow, EndLocation);
	}
}

void AXhWalkActorBase::XhChangeActors(const TArray<AActor*>& InRangeWalkActors, const TArray<AActor*>& OutRangeWalkActors, const TArray<AActor*>& WalkIgnoreActors, bool bAdd/* = true*/)
{
	if (WalkActorCompBase)
	{
		if (bAdd)
		{
			WalkActorCompBase->InRangeWalkActors.Append(InRangeWalkActors);
			WalkActorCompBase->InRangeWalkActors.Append(OutRangeWalkActors);
			WalkActorCompBase->InRangeWalkActors.Append(WalkIgnoreActors);
		}
		else
		{
			for (auto& a : InRangeWalkActors)
			{
				if (WalkActorCompBase->InRangeWalkActors.Contains(a))
				{
					WalkActorCompBase->InRangeWalkActors.Remove(a);
				}
			}
			for (auto& b : OutRangeWalkActors)
			{
				if (WalkActorCompBase->OutRangeWalkActors.Contains(b))
				{
					WalkActorCompBase->OutRangeWalkActors.Remove(b);
				}
			}
			for (auto& c : WalkIgnoreActors)
			{
				if (WalkActorCompBase->IgnoreActors.Contains(c))
				{
					WalkActorCompBase->IgnoreActors.Remove(c);
				}
			}
		}
	}
}

void AXhWalkActorBase::XhSetSplineMeshStyle(UStaticMesh* InSplineMeshStyle)
{
	if (WalkActorCompBase)
	{
		WalkActorCompBase->SplineMeshStyle = InSplineMeshStyle;
	}
}

// Called when the game starts or when spawned
void AXhWalkActorBase::BeginPlay()
{
	Super::BeginPlay();
	EndLocation->SetHiddenInGame(true,true);
	XhBegin();
}


// Called every frame
void AXhWalkActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

