// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Actor/XhActorBase.h"
#include "Base/Grab/XhGrabActorCompBase.h"
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

FTransform AXhActorBase::GetXhActorTransform(const FString& InName)
{
	if (XhGameState)
	{
		return XhGameState->GetXhActorTransform(InName);
	}
	return FTransform();
}

void AXhActorBase::XhDestroy()
{
	if(IsValid(this))
	{
		Destroy();
	}
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
		XhGameState = Cast<AXhGameState>(UGameplayStatics::GetGameState(World));
		XhPlayerController = Cast<AXhPlayerController>(UGameplayStatics::GetPlayerController(World, 0));
		if (XhPlayerController)
		{
			XhCharacter = XhPlayerController->GetPawn<AXhCharacter>();
			if (XhCharacter)
			{
				XhPlayerState = XhCharacter->GetPlayerState<AXhPlayerState>();
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
	}
	if (!XhGameState) 
	{
		UXhTool::WriteLog(this, TEXT("XhNativeInit:XhGameState获取失败！"));
	}
	if (!XhPlayerController)
	{
		UXhTool::WriteLog(this, TEXT("XhNativeInit:XhPlayerController获取失败！"));
	}
	if (!XhCharacter)
	{
		UXhTool::WriteLog(this, TEXT("XhNativeInit:XhCharacter获取失败！"));
	}
	if (!XhPlayerState)
	{
		UXhTool::WriteLog(this, TEXT("XhNativeInit:XhPlayerState获取失败！"));
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
	if (XhPlayerState && bCanOpera)
	{
		XhPlayerState->XhOperaActors.Remove(this);
	}
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AXhActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

