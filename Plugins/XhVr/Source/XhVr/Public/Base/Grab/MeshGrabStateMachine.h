// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Type/XhCore.h"
#include "MeshGrabStateMachine.generated.h"

/**
 * 
 */
UCLASS()
class XHVR_API UMeshGrabStateMachine : public UObject
{
	GENERATED_BODY()
public:
	UMeshGrabStateMachine();
	struct GrabAndHandState
	{
		EXhGrabState GrabState;
		EXhGrabStateEvent HandState;
	public:
		GrabAndHandState()
			: GrabState(EXhGrabState::None)
			, HandState(EXhGrabStateEvent::None)
		{

		}
		GrabAndHandState(EXhGrabState InXhGrabState, EXhGrabStateEvent InXhHand)
			: GrabState(InXhGrabState)
			, HandState(InXhHand)
		{

		}
		bool operator==(const GrabAndHandState B) const
		{
			return GrabState == B.GrabState && HandState == B.HandState;
		}
	};
public:
	EXhGrabState CurrentGrabState;
	EXhGrabState LastGrabState;
	TMap<int32, GrabAndHandState> GrabHandStateMap;
	TArray<EXhGrabState> NextGrabStateArray;

public:
	void InitMap();
	void GrabCompleted(EXhGrabStateEvent InHand);
	EXhGrabState NextGrabState(EXhGrabStateEvent InHand);
	EXhGrabState Overlap(EXhGrabStateEvent InHand);
	EXhGrabState Grab(EXhGrabStateEvent InHand);
	EXhGrabState Drop(EXhGrabStateEvent InHand);
};
