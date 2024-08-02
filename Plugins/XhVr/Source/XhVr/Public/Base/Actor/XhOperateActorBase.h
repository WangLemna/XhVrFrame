// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XhOperateActorBase.generated.h"

/**
 * 
 */
UCLASS()
class XHVR_API AXhOperateActorBase : public AXhActorBase
{
	GENERATED_BODY()
public:
	AXhOperateActorBase();
public:



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
