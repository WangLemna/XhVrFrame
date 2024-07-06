// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBase/XhWalkActorCompBase.h"
#include "GameBase/XhWalkActorBase.h"
#include "Components/ActorComponent.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMesh.h"
#include "IXRTrackingSystem.h"

DEFINE_LOG_CATEGORY(XhWalkActorCompBaseLog)
// Sets default values for this component's properties
UXhWalkActorCompBase::UXhWalkActorCompBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	SetAutoActivate(false);
	bRegisterCompleted = false;
	bStartWalk = false;
	bCanTick = false;
	ChildActorName = "";
	bIsDot = true;
	SimFrequency = 25.0f;
	WalkDistance = 500.0f;
	FadeInDuration = 0.2f;
	FadeOutDuration = 0.2f;
	DrawDebugType = EDrawDebugTrace::None;
	FadeColor = FLinearColor::Black;
	InitailLocationZ = 0;
}


void UXhWalkActorCompBase::ActivateEvent(UActorComponent* Component, bool bReset)
{
	if (SimFrequency > 0 && WalkDistance > 0)
	{
		bStartWalk = true;
		bCanTick = true;
	}
	else
	{
		UE_LOG(XhWalkActorCompBaseLog, Warning, TEXT("SimFrequency，WalkDistance参数有误！"));
	}
}

void UXhWalkActorCompBase::DeactivatedEvent(UActorComponent* Component)
{
	bCanTick = false;
	XhOverWalk();
}


void UXhWalkActorCompBase::XhStartWalk()
{
	if (!IsRegisterCompleted())
	{
		return;
	}
	Activate();
}

void UXhWalkActorCompBase::XhEndWalk()
{
	if (!IsRegisterCompleted())
	{
		return;
	}
	Deactivate();
}



void UXhWalkActorCompBase::XhWalk_Implementation()
{
	XhClearSpline();
	FHitResult Hit;
	TArray<FVector> PathPositions;
	bool bHit = XhSendSpline(Hit, PathPositions, WalkLocation);
	EWalkTraceHitResult WalkState;
	bValidSpline = XhGetWalkStateResult(Hit, bHit, WalkState);
	XhMakeSplineMesh(WalkState, PathPositions);
	XhUpdateEndMesh(WalkState, WalkLocation);
}

void UXhWalkActorCompBase::XhClearSpline_Implementation()
{
	for (auto& Temp : SplineMeshes)
	{
		Temp->DestroyComponent();
	}
	SplineMeshes.Empty();
	TraceSpline->ClearSplinePoints(true);
}

bool UXhWalkActorCompBase::XhSendSpline_Implementation(FHitResult& OutHit, TArray<FVector>& OutPathPositions, FVector& OutLastTraceDestination)
{
	//UGameplayStatics::PredictProjectilePath();
	FVector StartPos = WalkArrow->GetComponentLocation();
	FVector LaunchVelocity = WalkArrow->GetForwardVector() * WalkDistance;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQueryArray;
	ObjectTypeQueryArray.Add(EObjectTypeQuery::ObjectTypeQuery1);
	FPredictProjectilePathParams Params = FPredictProjectilePathParams(0.0, StartPos, LaunchVelocity, 2.0);
	Params.bTraceWithCollision = true;
	Params.bTraceComplex = false;
	Params.ActorsToIgnore = IgnoreActors;
	Params.DrawDebugType = DrawDebugType;
	Params.DrawDebugTime = 0.0;
	Params.SimFrequency = SimFrequency;
	Params.OverrideGravityZ = 0.0;
	Params.ObjectTypes = ObjectTypeQueryArray; //ECollisionChannel
	Params.bTraceWithChannel = false;

	// Do the trace
	FPredictProjectilePathResult PredictResult;
	bool bHit = UGameplayStatics::PredictProjectilePath(GetWorld(), Params, PredictResult);

	// Fill in results.
	OutHit = PredictResult.HitResult;
	OutLastTraceDestination = PredictResult.HitResult.Location;
	OutPathPositions.Empty(PredictResult.PathData.Num());
	for (const auto& PathPoint : PredictResult.PathData)
	{
		OutPathPositions.Add(PathPoint.Location);
	}
	return bHit;
}

bool UXhWalkActorCompBase::XhGetWalkStateResult_Implementation(FHitResult InHit, bool InHitResult, EWalkTraceHitResult& OutWalkState)
{
	if (!InHitResult)
	{
		OutWalkState = EWalkTraceHitResult::None;
		return false;
	}
	else if (InRangeWalkActors.Contains(InHit.GetActor()))
	{

		OutWalkState = EWalkTraceHitResult::InRange;
		return true;
	}
	else if (OutRangeWalkActors.Contains(InHit.GetActor()))
	{
		OutWalkState = EWalkTraceHitResult::OutRange;
		return false;
	}
	OutWalkState = EWalkTraceHitResult::None;
	return false;
}


void UXhWalkActorCompBase::XhMakeSplineMesh(EWalkTraceHitResult InWalkState, TArray<FVector> InPathPositions)
{
	switch (InWalkState)
	{
	case EWalkTraceHitResult::None:
		XhMakeSplineMeshNone(InPathPositions);
		break;
	case EWalkTraceHitResult::InRange:
		XhMakeSplineMeshInRange(InPathPositions);
		break;
	case EWalkTraceHitResult::OutRange:
		XhMakeSplineMeshOutRange(InPathPositions);
		break;
	default:
		break;
	}
}

void UXhWalkActorCompBase::XhMakeSplineMeshNone_Implementation(const TArray<FVector>& InPathPositions)
{

}

void UXhWalkActorCompBase::XhMakeSplineMeshInRange_Implementation(const TArray<FVector>& InPathPositions)
{
	for (FVector Temp : InPathPositions)
	{
		TraceSpline->AddSplinePoint(Temp, ESplineCoordinateSpace::Local);
	}
	TraceSpline->SetSplinePointType(InPathPositions.Num(), ESplinePointType::CurveClamped);
	int32 SplinePointsIndex = TraceSpline->GetNumberOfSplinePoints() - 2;
	for (int32 i = 0; i < SplinePointsIndex; i++)
	{
		USplineMeshComponent* SplineMeshComponent = Cast<USplineMeshComponent>(TraceSpline->GetOwner()->AddComponentByClass(USplineMeshComponent::StaticClass(), true, FTransform(), false));
		SplineMeshComponent->SetMobility(EComponentMobility::Movable);
		SplineMeshComponent->SetStaticMesh(SplineMeshStyle);
		if (SplineMeshComponent)
		{
			SplineMeshes.Add(SplineMeshComponent);
			FVector StartPos = InPathPositions[i];
			FVector EndPos = InPathPositions[i + 1];
			if (bIsDot)
			{
				EndPos += (StartPos - EndPos) / 2.0;
			}
			SplineMeshComponent->SetStartAndEnd(StartPos, FVector::ZeroVector, EndPos, FVector::ZeroVector);
		}
		else
		{
			break;
		}
	}
}

void UXhWalkActorCompBase::XhMakeSplineMeshOutRange_Implementation(const TArray<FVector>& InPathPositions)
{

}


void UXhWalkActorCompBase::XhUpdateEndMesh(EWalkTraceHitResult InWalkState, FVector InLastTraceDestination)
{
	switch (InWalkState)
	{
	case EWalkTraceHitResult::None:
		XhUpdateEndMeshNone(InLastTraceDestination);
		break;
	case EWalkTraceHitResult::InRange:
		XhUpdateEndMeshInRange(InLastTraceDestination);
		break;
	case EWalkTraceHitResult::OutRange:
		XhUpdateEndMeshOutRange(InLastTraceDestination);
		break;
	default:
		break;
	}
}

void UXhWalkActorCompBase::XhUpdateEndMeshNone_Implementation(FVector InLastTraceDestination)
{
	WalkEnd->SetHiddenInGame(true, true);
}

void UXhWalkActorCompBase::XhUpdateEndMeshInRange_Implementation(FVector InLastTraceDestination)
{
	WalkEnd->SetWorldLocation(InLastTraceDestination + EndInitLocation);
	FRotator EndRotator = FRotator::ZeroRotator;
	if (GEngine->XRSystem.IsValid() && GEngine->XRSystem->IsHeadTrackingAllowed())
	{
		FQuat OrientationAsQuat;
		FVector Position(0.f);

		GEngine->XRSystem->GetCurrentPose(IXRTrackingSystem::HMDDeviceId, OrientationAsQuat, Position);

		EndRotator = OrientationAsQuat.Rotator();
	}
	EndRotator = FRotator(EndInitRotation.Pitch, WalkRotationYaw + EndRotator.Yaw + EndInitRotation.Yaw, EndInitRotation.Roll);
	WalkEnd->SetWorldRotation(EndRotator);
	WalkEnd->SetHiddenInGame(false, true);
}

void UXhWalkActorCompBase::XhUpdateEndMeshOutRange_Implementation(FVector InLastTraceDestination)
{
	WalkEnd->SetHiddenInGame(false, true);
}


void UXhWalkActorCompBase::XhOverWalk_Implementation()
{
	if (bStartWalk && !bIsWalking && GetWorld())
	{
		if (bValidSpline)
		{
			bIsWalking = true;
			FVector FinalWalkLocation;
			FRotator FinalWalkRotation;
			XhGetWalkLocarionAndRotation(FinalWalkLocation, FinalWalkRotation);

			if (FadeInDuration < GetWorld()->GetDeltaSeconds())
			{
				XhWalker->SetActorLocationAndRotation(FinalWalkLocation, FinalWalkRotation);
				XhClearWalk();
				bIsWalking = false;
				XhClearSpline();
				bStartWalk = false;
			}
			else
			{
				APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
				if (PlayerCameraManager)
				{
					PlayerCameraManager->StartCameraFade(0.f, 1.f, FadeInDuration, FadeColor, false, true);
					UKismetSystemLibrary::Delay(GetWorld(), FadeInDuration, FLatentActionInfo());
					//GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyCharacter::TimerFunction, 5.f, true);
					FTimerHandle FadeInTimerHandle;
					FTimerHandle FadeOutTimerHandle;
					auto FadeOut = [&] {
						if (FadeOutTimerHandle.IsValid())
						{
							GetWorld()->GetTimerManager().ClearTimer(FadeOutTimerHandle);
						}
						XhClearWalk();
						bIsWalking = false;
						XhClearSpline();
						bStartWalk = false;
					};
					auto FadeIn = [&] {
						if (FadeInTimerHandle.IsValid())
						{
							GetWorld()->GetTimerManager().ClearTimer(FadeInTimerHandle);
						}
						XhWalker->SetActorLocationAndRotation(FinalWalkLocation, FinalWalkRotation);
						PlayerCameraManager->StartCameraFade(1.f, 0.f, FadeOutDuration, FadeColor, false, false);
						GetWorld()->GetTimerManager().SetTimer(FadeOutTimerHandle, FadeOut, FadeOutDuration, false);
					};
					GetWorld()->GetTimerManager().SetTimer(FadeInTimerHandle, FadeIn, FadeInDuration, false);
					return;
				}
			}
		}
		else
		{
			XhClearWalk();
		}
	}
	else
	{
		XhClearWalk();
	}
}

void UXhWalkActorCompBase::XhGetWalkLocarionAndRotation_Implementation(FVector& OutLocation, FRotator& OutRotation)
{
	OutRotation = FRotator(0, XhWalker->GetActorRotation().Yaw + WalkRotationYaw, 0);
	FVector Position(0.f);
	if (GEngine->XRSystem.IsValid() && GEngine->XRSystem->IsHeadTrackingAllowed())
	{
		FQuat OrientationAsQuat;

		GEngine->XRSystem->GetCurrentPose(IXRTrackingSystem::HMDDeviceId, OrientationAsQuat, Position);
		Position.Z = 0.f;
	}
	FVector RotatorVector = OutRotation.RotateVector(Position);
	OutLocation = WalkLocation - RotatorVector + FVector(0.f, 0.f, InitailLocationZ);
}

void UXhWalkActorCompBase::XhClearWalk_Implementation()
{
	if (bStartWalk)
	{
		bStartWalk = false;
		WalkEnd->SetHiddenInGame(true, true);
		WalkRotationYaw = 0.f;
	}
}

bool UXhWalkActorCompBase::XhRegisterWalkActor(AActor* InWalker, USplineComponent* InTraceSpline, UArrowComponent* InWalkArrow, UStaticMeshComponent* InEndLocation)
{
	if (InTraceSpline->GetOwner() == InWalkArrow->GetOwner() && InWalkArrow->GetOwner() == InEndLocation->GetOwner())
	{
		XhWalker = InWalker;
		TraceSpline = InTraceSpline;
		WalkArrow = InWalkArrow;
		WalkEnd = InEndLocation;
		EndInitLocation = WalkEnd->GetRelativeLocation();
		EndInitRotation = WalkEnd->GetRelativeRotation();
		IgnoreActors.AddUnique(InTraceSpline->GetOwner());
		IgnoreActors.AddUnique(XhWalker);
		bRegisterCompleted = true;
	}
	else
	{
		bRegisterCompleted = false;
	}
	return bRegisterCompleted;
}

void UXhWalkActorCompBase::XhPrint()
{
	UKismetSystemLibrary::Delay(GetWorld(), 2.f, FLatentActionInfo());
	UE_LOG(XhWalkActorCompBaseLog, Error, TEXT("adsdasdsadasdsa"));
}

// Called when the game starts
void UXhWalkActorCompBase::BeginPlay()
{
	Super::BeginPlay();

	Deactivate();
	// ...
	IgnoreActors.AddUnique(GetOwner());
	InitWalkActor();
	XhBegin();
}

void UXhWalkActorCompBase::InitWalkActor()
{
	if (GetOwner())
	{
		OnComponentActivated.AddDynamic(this, &UXhWalkActorCompBase::ActivateEvent);
		OnComponentDeactivated.AddDynamic(this, &UXhWalkActorCompBase::DeactivatedEvent);

		if (!ChildActorName.IsEmpty())
		{
			TArray<UChildActorComponent*> ChildActorComps;
			AXhWalkActorBase* XhWalkActorBase = nullptr;
			GetOwner()->GetComponents(UChildActorComponent::StaticClass(), ChildActorComps, true);
			for (auto& Temp : ChildActorComps)
			{
				if (ChildActorName == GetNameSafe((Temp)))
				{
					XhWalkActorBase = Cast<AXhWalkActorBase>(Temp->GetChildActor());
					if (XhWalkActorBase)
					{
						break;
					}
				}
			}
			if (XhWalkActorBase)
			{
				XhRegisterWalkActor(GetOwner(), XhWalkActorBase->TraceSpline, XhWalkActorBase->WalkArrow, XhWalkActorBase->EndLocation);
			}
			else
			{
				UE_LOG(XhWalkActorCompBaseLog, Warning, TEXT("未获取到XhWalkActorBase,请自行注册！"));
			}
		}
		else
		{
			UE_LOG(XhWalkActorCompBaseLog, Warning, TEXT("未获取到ChildActorName,请自行注册！"));
		}

	}
}

// Called every frame
void UXhWalkActorCompBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (bCanTick && IsRegisterCompleted())
	{
		XhWalk();
	}
}

