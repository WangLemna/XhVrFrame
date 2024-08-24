// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/IXhOculusEvent.h"
#include "Base/Actor/XhActorBase.h"
#include "XhOperateActorBase.generated.h"

class UXhGrabActorCompBase;

/**
 * 
 */
UCLASS()
class XHVR_API AXhOperateActorBase : public AXhActorBase, public IXhOculusEvent
{
	GENERATED_BODY()
public:
	AXhOperateActorBase();
public:
	//XhRegisterGrabMeshComps()
	//LeftGrabCollisionComps  RightGrabCollisionComps
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UXhGrabActorCompBase> GrabActorCompBase;

protected:
	UXhGrabActorCompBase* GrabComp;
public:
	//抓取
	UFUNCTION(BlueprintCallable, meta = (Keywords = "XhGrab"))
	void XhGrab(UStaticMeshComponent* InMeshComp, USceneComponent* InAttchParent, EXhGrabStateEvent InGrabStateEvent = EXhGrabStateEvent::Max, const FName SocketName = NAME_None, float DelayAttch = 0);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XhVar|Settings")
	bool bAutoInitGrab;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void InitGrab();
	void XhNativeInit();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
