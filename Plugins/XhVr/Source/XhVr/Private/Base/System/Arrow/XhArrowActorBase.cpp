// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/System/Arrow/XhArrowActorBase.h"
#include "Runtime/UMG/Public/Components/WidgetComponent.h"

// Sets default values
AXhArrowActorBase::AXhArrowActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AXhArrowActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXhArrowActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

