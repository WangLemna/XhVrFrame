// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Trace/XhTraceActorBase.h"
#include "Base/Trace/XhTraceActorCompBase.h"
#include "Components/ArrowComponent.h"
#include "Components/WidgetInteractionComponent.h"

// Sets default values
AXhTraceActorBase::AXhTraceActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TraceRoot = CreateDefaultSubobject<USceneComponent>(TEXT("TraceRoot"));
	XhTrace = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("XhTrace"));
	XhHitPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("XhHitPoint"));
	TraceArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("TraceArrow"));
	WidgetTrace = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetTrace"));
	TraceActorCompBase = CreateDefaultSubobject<UXhTraceActorCompBase>(TEXT("WalkActorCompBase"));

	RootComponent = TraceRoot;
	XhTrace->SetupAttachment(TraceRoot);
	XhHitPoint->SetupAttachment(TraceRoot);
	TraceArrow->SetupAttachment(TraceRoot);
	WidgetTrace->SetupAttachment(TraceRoot);

}

void AXhTraceActorBase::XhEnableTrace(bool InWidgetTraceEnable)
{
	if (TraceActorCompBase)
	{
		TraceActorCompBase->XhEnableTrace(InWidgetTraceEnable);
	}
}

void AXhTraceActorBase::XhDisableTrace()
{
	if (TraceActorCompBase)
	{
		TraceActorCompBase->XhDisableTrace();
	}
}

void AXhTraceActorBase::XhSetTraceMode(EXhTraceMode InTraceMode)
{
	if (TraceActorCompBase)
	{
		TraceActorCompBase->XhSetTraceMode(InTraceMode);
	}
}

void AXhTraceActorBase::XhRegisterTraceActor()
{
	if (TraceActorCompBase)
	{
		TraceActorCompBase->XhRegisterTraceActor(XhTrace, XhHitPoint, TraceArrow, WidgetTrace);
	}
}

void AXhTraceActorBase::XhChangeActors(const TArray<AActor*>& TraceIgnoreActors, bool bAdd /*= true*/)
{
	if (TraceActorCompBase)
	{
		if (bAdd)
		{
			TraceActorCompBase->IgnoreActors.Append(TraceIgnoreActors);
		}
		else
		{
			for (auto& a : TraceIgnoreActors)
			{
				if (TraceActorCompBase->IgnoreActors.Contains(a))
				{
					TraceActorCompBase->IgnoreActors.Remove(a);
				}
			}
		}
	}
}

void AXhTraceActorBase::XhClickStarted()
{
	if (TraceActorCompBase)
	{
		TraceActorCompBase->XhClickStarted();
	}
}

void AXhTraceActorBase::XhClickCompleted()
{
	if (TraceActorCompBase)
	{
		TraceActorCompBase->XhClickCompleted();
	}
}

// Called when the game starts or when spawned
void AXhTraceActorBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AXhTraceActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

