// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Actor/XhActorBase.h"
#include "Base/GameBase/XhGameState.h"
#include "Base/GameBase/XhPlayerController.h"
#include "Base/GameBase/XhPlayerState.h"
#include "Base/GameBase/XhCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AXhActorBase::AXhActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	XhBeginOrder = -1;
	bCanOpera = false;
	XhActorId = TEXT_EMPTY;
}

bool AXhActorBase::GetCanOpera()
{
	return bCanOpera;
}

AXhActorBase* AXhActorBase::GetXhActorById(const FString& InId)
{
	if (XhPlayerState)
	{
		return XhPlayerState->GetXhActorById(InId);
	}
	return nullptr;
}

TArray<AXhActorBase*> AXhActorBase::GetXhActorsByClassName(const FString& InClassName)
{
	TArray<AXhActorBase*> Results;
	if (XhPlayerState)
	{
		return XhPlayerState->GetXhActorsByClassName(InClassName);
	}
	return Results;
}

void AXhActorBase::ChangeCanOpera(bool InCanOpera)
{
	if (bCanOpera == InCanOpera)
	{
		return;
	}
	else
	{
		if (XhPlayerState)
		{
			if (InCanOpera)
			{
				XhPlayerState->XhOperaActors.AddUnique(this);
			}
			else
			{
				XhPlayerState->XhOperaActors.Remove(this);
			}
			bCanOpera = InCanOpera;
		}
		else
		{
			this, TEXT("ChangeCanOpera:XhPlayerState不存在！操作失败！");
		}
	}
}

void AXhActorBase::XhNativeInit()
{
	//初始化变量
	XhClassName = GetClass()->GetName().LeftChop(2);//xxxx_C -> xxxx
	if (UWorld* World = GetWorld())
	{
		if (XhPlayerState)
		{
			if (XhActorId != TEXT_EMPTY)
			{
				XhPlayerState->XhActorsDataById.Add(XhActorId, this);
			}
			if (XhPlayerState->XhActorsData.Contains(XhClassName))
			{
				XhPlayerState->XhActorsData.Find(XhClassName)->XhActorBaseArray.AddUnique(this);
			}
			else
			{
				XhPlayerState->XhActorsData.Add(XhClassName, FXhActorBaseArray({ this }));
			}
			if (bCanOpera)
			{
				XhPlayerState->XhOperaActors.AddUnique(this);
			}
		}
	}

}

// Called when the game starts or when spawned
void AXhActorBase::BeginPlay()
{
	XH_BP_EXEC_B(XhBegin);
	Super::BeginPlay();
	XhNativeInit();
	XH_BP_EXEC_E(XhBegin);
	
}


void AXhActorBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (XhPlayerState)
	{
		XhPlayerState->XhActorsData[XhClassName].XhActorBaseArray.Remove(this);
		if (bCanOpera)
		{
			XhPlayerState->XhOperaActors.Remove(this);
		}
	}
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AXhActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

