// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Trace/XhTraceActorCompBase.h"
#include "Base/Trace/XhTraceActorBase.h"
#include "Components/ArrowComponent.h"
#include "Components/WidgetInteractionComponent.h"

DEFINE_LOG_CATEGORY(XhTraceActorCompBaseLog)
// Sets default values for this component's properties
UXhTraceActorCompBase::UXhTraceActorCompBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	ChildActorName = "";
	TraceDistance = 500.f;
	TraceSize = FVector2D(1.f);
	HitPointForwardDistance = 2.f;
	TraceMode = EXhTraceMode::Trace;
	DrawDebugType = EDrawDebugTrace::None;
}


void UXhTraceActorCompBase::ActivateEvent(UActorComponent* Component, bool bReset)
{
	if (XhWidgetTrace)
	{
		XhWidgetTrace->InteractionDistance = TraceDistance;
		//XhWidgetTrace->Activate();
		XhWidgetTrace->SetActive(bWidgetTraceEnable);
	}
	XhTrace->SetWorldScale3D(FVector(0, TraceSize.X, TraceSize.Y));
	XhTrace->SetStaticMesh(TraceMeshStyle);
	XhHitPoint->SetStaticMesh(HitPointMeshStyle);
	bCanTick = true;
}

void UXhTraceActorCompBase::DeactivatedEvent(UActorComponent* Component)
{
	if (XhWidgetTrace)
	{
		XhWidgetTrace->Deactivate();
	}
	XhTrace->SetWorldScale3D(FVector(0, TraceSize.X, TraceSize.Y));
	XhTrace->SetStaticMesh(nullptr);
	XhHitPoint->SetStaticMesh(nullptr);
	bCanTick = false;
}

void UXhTraceActorCompBase::XhEnableTrace(bool InWidgetTraceEnable)
{
	if (!IsRegisterCompleted())
	{
		return;
	}
	bWidgetTraceEnable = InWidgetTraceEnable;
	Activate();
}

void UXhTraceActorCompBase::XhDisableTrace()
{
	if (!IsRegisterCompleted())
	{
		return;
	}
	Deactivate();
}

void UXhTraceActorCompBase::XhSetTraceMode(EXhTraceMode InTraceMode)
{
	TraceMode = InTraceMode;
}

void UXhTraceActorCompBase::XhClickStarted()
{
	if (XhWidgetTrace && XhWidgetTrace->IsActive())
	{
		XhWidgetTrace->PressPointerKey(FKey("LeftMouseButton"));
	}
}

void UXhTraceActorCompBase::XhClickCompleted()
{
	if (XhWidgetTrace && XhWidgetTrace->IsActive())
	{
		XhWidgetTrace->ReleasePointerKey(FKey("LeftMouseButton"));
	}
}

void UXhTraceActorCompBase::XhSendTrace_Implementation()
{
	FHitResult OutHit;
	XhGetHitResult(OutHit);
	XhHitResult(OutHit);
}

void UXhTraceActorCompBase::XhGetHitResult_Implementation(FHitResult& OutHit)
{
	OutHit = FHitResult();
	switch (TraceMode)
	{
	case EXhTraceMode::Widget:
	{
		if (XhWidgetTrace && bWidgetTraceEnable)
		{
			OutHit = XhWidgetTrace->GetLastHitResult();
		}
	}
		break;
	case EXhTraceMode::Trace:
	{
		FVector Start = XhArrow->GetComponentLocation();
		FVector End = XhArrow->GetForwardVector() * TraceDistance + Start;
		UKismetSystemLibrary::LineTraceSingle(this, Start, End, ETraceTypeQuery::TraceTypeQuery1, false, IgnoreActors, DrawDebugType, OutHit, true, FLinearColor::Red, FLinearColor::Blue, 5.0);
	}
		break;
	default:
		break;
	}
}

void UXhTraceActorCompBase::XhHitResult(const FHitResult& InHit)
{
	if (InHit.bBlockingHit)
	{
		XhHitResultTrue(InHit);
	}
	else
	{
		XhHitResultFalse(InHit);
	}
}

void UXhTraceActorCompBase::XhHitResultTrue_Implementation(const FHitResult& InHit)
{
	float Distance = FVector::Distance(XhArrow->GetComponentLocation(), InHit.ImpactPoint) - HitPointForwardDistance;
	FVector TraceScale = FVector(Distance, XhTrace->GetComponentScale().Y, XhTrace->GetComponentScale().Z);
	XhTrace->SetWorldScale3D(TraceScale);
	FVector HitPointLocation = XhArrow->GetComponentLocation() + XhArrow->GetForwardVector() * Distance;
	XhHitPoint->SetWorldLocation(HitPointLocation);
	XhHitPoint->SetHiddenInGame(false, true);
}

void UXhTraceActorCompBase::XhHitResultFalse_Implementation(const FHitResult& InHit)
{
	XhTrace->SetWorldScale3D(FVector(TraceDistance, TraceSize.X, TraceSize.Y));
	XhHitPoint->SetWorldLocation(FVector::ZeroVector);
	XhHitPoint->SetHiddenInGame(true, true);
}

bool UXhTraceActorCompBase::XhRegisterTraceActor(UStaticMeshComponent* InTrace, UStaticMeshComponent* InHitPoint, UArrowComponent* InArrow, UWidgetInteractionComponent* InWidgetTrace)
{
	if (InTrace->GetOwner() == InHitPoint->GetOwner() && InHitPoint->GetOwner() == InArrow->GetOwner())
	{
		XhTrace = InTrace;
		XhHitPoint = InHitPoint;
		XhArrow = InArrow;
		XhWidgetTrace = InWidgetTrace;
		IgnoreActors.AddUnique(InTrace->GetOwner());
		bRegisterCompleted = true;
	}
	else
	{
		bRegisterCompleted = false;
	}
	return bRegisterCompleted;
}

// Called when the game starts
void UXhTraceActorCompBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Deactivate();
	// ...
	IgnoreActors.AddUnique(GetOwner());
	InitTraceActor();
	XhBegin();
}


void UXhTraceActorCompBase::InitTraceActor()
{
	if (GetOwner())
	{
		OnComponentActivated.AddDynamic(this, &UXhTraceActorCompBase::ActivateEvent);
		OnComponentDeactivated.AddDynamic(this, &UXhTraceActorCompBase::DeactivatedEvent);

		if (!ChildActorName.IsEmpty())
		{
			TArray<UChildActorComponent*> ChildActorComps;
			AXhTraceActorBase* XhTraceActorBase = nullptr;
			GetOwner()->GetComponents(UChildActorComponent::StaticClass(), ChildActorComps, true);
			for (auto& Temp : ChildActorComps)
			{
				if (ChildActorName == GetNameSafe((Temp)))
				{
					XhTraceActorBase = Cast<AXhTraceActorBase>(Temp->GetChildActor());
					if (XhTraceActorBase)
					{
						break;
					}
				}
			}
			if (XhTraceActorBase)
			{
				//XhRegisterTraceActor(GetOwner(), XhTraceActorBase->TraceSpline, XhTraceActorBase->WalkArrow, XhTraceActorBase->EndLocation);
			}
			else
			{
				UE_LOG(XhTraceActorCompBaseLog, Warning, TEXT("未获取到XhTraceActorBase,请自行注册！"));
			}
		}
		else
		{
			UE_LOG(XhTraceActorCompBaseLog, Warning, TEXT("未获取到ChildActorName,请自行注册！"));
		}

	}
}

// Called every frame
void UXhTraceActorCompBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (bCanTick && IsRegisterCompleted())
	{
		XhSendTrace();
	}
}

