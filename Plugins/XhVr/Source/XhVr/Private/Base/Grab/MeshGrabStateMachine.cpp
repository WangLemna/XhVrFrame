// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Grab/MeshGrabStateMachine.h"

UMeshGrabStateMachine::UMeshGrabStateMachine()
{
	CurrentGrabState = EXhGrabState::None;
	LastGrabState = EXhGrabState::None;
	InitMap();
	//NextGrabStateArray = {
	//	//None
	//	EXhGrabState::LeftOverlap,
	//	EXhGrabState::RightOverlap,
	//	EXhGrabState::Grabbing,
	//	EXhGrabState::Grabbing,
	//	//LeftOverlap
	//	EXhGrabState::None,
	//	EXhGrabState::AllOverlap,
	//	EXhGrabState::Grabbing,
	//	EXhGrabState::Grabbing,
	//	//RightOverlap
	//	EXhGrabState::AllOverlap,
	//	EXhGrabState::None,
	//	EXhGrabState::Grabbing,
	//	EXhGrabState::Grabbing,
	//	//AllOverlap
	//	EXhGrabState::None,
	//	EXhGrabState::None,
	//	EXhGrabState::Grabbing,
	//	EXhGrabState::Grabbing,
	//	//LeftGrab
	//	EXhGrabState::None,
	//	EXhGrabState::LeftGrabRightOverlap,
	//	EXhGrabState::Grabbing,
	//	EXhGrabState::Grabbing,
	//	//RightGrab
	//	EXhGrabState::RightGrabLeftOverlap,
	//	EXhGrabState::None,
	//	EXhGrabState::Grabbing,
	//	EXhGrabState::Grabbing,
	//	//Grabbing
	//	EXhGrabState::None,
	//	EXhGrabState::None,
	//	EXhGrabState::None,
	//	EXhGrabState::None,
	//};
}

void UMeshGrabStateMachine::InitMap()
{
	int32 MapKey = 0;
	for (uint8 i = 0; i < (uint8)EXhGrabState::Max; i++)
	{
		for (uint8 j = 1; j < (uint8)EXhGrabStateEvent::Max; j++)
		{
			GrabHandStateMap.Add(MapKey++, GrabAndHandState((EXhGrabState)i, (EXhGrabStateEvent)j));
		}
	}
}

void UMeshGrabStateMachine::GrabCompleted(EXhGrabStateEvent InHand)
{
	//CurrentGrabState = InHand;
}

EXhGrabState UMeshGrabStateMachine::NextGrabState(EXhGrabStateEvent InHand)
{
	if (const int32* IndexPtr = GrabHandStateMap.FindKey(GrabAndHandState(CurrentGrabState, InHand)))
	{
		if (NextGrabStateArray[*IndexPtr] != EXhGrabState::None)
		{
			LastGrabState = CurrentGrabState;
			CurrentGrabState = NextGrabStateArray[*IndexPtr];
		}
	}
	return CurrentGrabState;
}

EXhGrabState UMeshGrabStateMachine::Overlap(EXhGrabStateEvent InHand)
{
	return EXhGrabState::None;
}

EXhGrabState UMeshGrabStateMachine::Grab(EXhGrabStateEvent InHand)
{
	return EXhGrabState::None;
}

EXhGrabState UMeshGrabStateMachine::Drop(EXhGrabStateEvent InHand)
{
	return EXhGrabState::None;
}
