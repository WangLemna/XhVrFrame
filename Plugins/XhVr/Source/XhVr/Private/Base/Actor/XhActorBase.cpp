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
	GrabComp = nullptr;
	bCanOpera = false;
}

void AXhActorBase::XhGrab(UStaticMeshComponent* InMeshComp, USceneComponent* InAttchParent, EXhGrabStateEvent InGrabStateEvent /*= EXhGrabStateEvent::Max*/, const FName& SocketName /*= NAME_None*/, float DelayAttch /*= 0*/)
{
	if (GrabComp)
	{
		GrabComp->XhGrab(InMeshComp, InAttchParent, InGrabStateEvent, SocketName, DelayAttch);
	}
	else
	{
		UXhTool::WriteLog(this, TEXT("XhGrab:GrabComp无效！"));
	}
}

bool AXhActorBase::GetCanOpera()
{
	return bCanOpera;
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
	XhClassName = GetClass()->GetName().LeftChop(2);
	GrabComp = GetComponentByClass<UXhGrabActorCompBase>();
	if (GrabComp)
	{
		GrabComp = GrabComp->IsActive() ? GrabComp : nullptr;
	}
	if (UWorld* World = GetWorld())
	{
		XhGameState = Cast<AXhGameState>(UGameplayStatics::GetGameState(World));
		if (!XhGameState)
		{
			UXhTool::WriteLog(this, TEXT("XhNativeInit:XhGameState获取失败！"));
		}
		XhPlayerController = Cast<AXhPlayerController>(UGameplayStatics::GetPlayerController(World, 0));
		if (XhPlayerController)
		{
			XhCharacter = XhPlayerController->GetPawn<AXhCharacter>();
			if (XhCharacter)
			{
				XhPlayerState = XhCharacter->GetPlayerState<AXhPlayerState>();
				if (XhPlayerState)
				{
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
				else
				{
					UXhTool::WriteLog(this, TEXT("XhNativeInit:XhPlayerState获取失败！"));
				}
			}
			else
			{
				UXhTool::WriteLog(this, TEXT("XhNativeInit:XhCharacter获取失败！"));
				UXhTool::WriteLog(this, TEXT("XhNativeInit:XhPlayerState获取失败！"));

			}
		}
		else
		{
			UXhTool::WriteLog(this, TEXT("XhNativeInit:XhPlayerController获取失败！"));
			UXhTool::WriteLog(this, TEXT("XhNativeInit:XhCharacter获取失败！"));
			UXhTool::WriteLog(this, TEXT("XhNativeInit:XhPlayerState获取失败！"));
		}
	}
	else
	{
		UXhTool::WriteLog(this, TEXT("XhNativeInit:XhGameState获取失败！"));
		UXhTool::WriteLog(this, TEXT("XhNativeInit:XhPlayerController获取失败！"));
		UXhTool::WriteLog(this, TEXT("XhNativeInit:XhCharacter获取失败！"));
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

