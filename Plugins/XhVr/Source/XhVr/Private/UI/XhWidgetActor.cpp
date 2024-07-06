// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XhWidgetActor.h"
#include "UI/XhUserWidget.h"
#include "Components/WidgetComponent.h"
#include "UI/XhButton.h"

// Sets default values
AXhWidgetActor::AXhWidgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AXhWidgetActor::Init()
{
	TArray<USceneComponent*> ChildComps;
	RootComponent->GetChildrenComponents(true, ChildComps);
	for (auto var : ChildComps)
	{
		if (UWidgetComponent* Temp = Cast<UWidgetComponent>(var))
		{
			if (UXhUserWidget* XhWidget = Cast<UXhUserWidget>(Temp->GetUserWidgetObject()))
			{
				XhWidget->XhWidgetActor = this;
				XhWidget->Init();
			}
		}
	}
}

// Called when the game starts or when spawned
void AXhWidgetActor::BeginPlay()
{
	Super::BeginPlay();
	Init();
	XhBegin();
}

// Called every frame
void AXhWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

