// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/GameBase/XhPlayerState.h"

TArray<AXhActorBase*> AXhPlayerState::GetXhActorsByClassName(const FString& InClassName)
{
	return XhActorsData[InClassName].XhActorBaseArray;
}

AXhActorBase* AXhPlayerState::GetXhActorById(const FString& InId)
{
	return XhActorsDataById[InId];
}
