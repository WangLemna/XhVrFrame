// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/GameBase/XhPlayerState.h"
#include "Base/Actor/XhActorBase.h"

TArray<AXhActorBase*> AXhPlayerState::GetXhActorsByClassName(const FString& InClassName)
{
	if (!XhActorsData.Contains(InClassName))
	{
		return {};
	}
	return XhActorsData[InClassName].XhActorBaseArray;
}

AXhActorBase* AXhPlayerState::GetXhActorById(const FString& InId)
{
	if (!XhActorsDataById.Contains(InId))
	{
		return nullptr;
	}
	return XhActorsDataById[InId];
}

TArray<AXhActorBase*> AXhPlayerState::GetXhActors(const FString& InId, const FString& InClassName, FName InTagName)
{
	TArray<AXhActorBase*> Result;
	if (InId != TEXT_EMPTY)
	{
		Result.Add(GetXhActorById(InId));
		return Result;
	}
	if (InClassName != TEXT_EMPTY)
	{
		Result = GetXhActorsByClassName(InClassName);
		if (InTagName != NAME_None && InTagName != FName(TEXT("")))
		{
			for (AXhActorBase* Temp : Result)
			{
				if (!Temp->ActorHasTag(InTagName))
				{
					Result.Remove(Temp);
				}
			}
		}
		return Result;
	}
	return Result;
}
