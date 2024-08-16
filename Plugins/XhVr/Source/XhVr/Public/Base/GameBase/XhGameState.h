// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "XhGameState.generated.h"

/**
 * 
 */
UCLASS()
class XHVR_API AXhGameState : public AGameState
{
	GENERATED_BODY()

protected:
	/** Overridable native event for when play begins for this actor. */
	virtual void BeginPlay() override;
};
