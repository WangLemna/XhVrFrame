// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/GameBase/XhGameState.h"
#include "Base/GameBase/XhGameMode.h"
//#include "Base/GameBase/XhCharacter.h"
#include "Kismet/GameplayStatics.h"

AXhGameState::AXhGameState()
{
	XhBeginOrder = -1;
}

FTransform AXhGameState::GetXhActorTransform(const FString& InName)
{
	if (ActorsTransform.Contains(InName))
	{
		return ActorsTransform[InName];
	}
	return FTransform();
}

void AXhGameState::XhNativeInit()
{
	XhGameMode = Cast<AXhGameMode>(GetWorld()->GetAuthGameMode());
	if (XhGameMode && XhGameMode->DT_ActorTransform)
	{
		TArray<FActorTransform*> ActorTransformData;
		XhGameMode->DT_ActorTransform->GetAllRows<FActorTransform>(TEXT(""), ActorTransformData);
		for (auto& Temp : ActorTransformData)
		{
			ActorsTransform.Add(Temp->Name, Temp->Transform);
		}
	}
// 	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
// 	{
// 		XhCharacter = Cast<AXhCharacter>(PC->GetPawn());
// 	}
	XhGameInstance = Cast<UXhGameInstance>(GetWorld()->GetGameInstance());
}

void AXhGameState::BeginPlay()
{
	XH_BP_EXEC_B(XhBegin);
	Super::BeginPlay();
	XhNativeInit();
	XH_BP_EXEC_E(XhBegin);
}
