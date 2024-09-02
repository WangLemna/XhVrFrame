// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/IXhOculusEvent.h"
#include "Base/Actor/XhActorBase.h"
#include "XhOperateActorBase.generated.h"

class UXhGrabActorCompBase;
class UXhGrabMeshComponent;

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
	//~ Begin IXhOculusEvent Interface.
public:
	void OculusA_Implementation(EButtonEvent InButtonEvent);
	void OculusB_Implementation(EButtonEvent InButtonEvent);
	void OculusX_Implementation(EButtonEvent InButtonEvent);
	void OculusY_Implementation(EButtonEvent InButtonEvent);
	void OculusJoystickL_Implementation(EButtonEvent InButtonEvent);
	void OculusJoystickR_Implementation(EButtonEvent InButtonEvent);
	void OculusGripL_Implementation(EButtonEvent InButtonEvent);
	void OculusGripR_Implementation(EButtonEvent InButtonEvent);
	void OculusTriggerL_Implementation(EButtonEvent InButtonEvent);
	void OculusTriggerR_Implementation(EButtonEvent InButtonEvent);
	//~ End IXhOculusEvent Interface.
protected:
	UXhGrabActorCompBase* GrabComp;
	TMap<FOculusEventMode, TArray<UXhGrabMeshComponent*>> XhGrabMeshCompEventMap;
	//TArray<UXhGrabMeshComponent*> XhGrabMeshCompArray;
public:
	//注册GrabMeshComponent
	UFUNCTION(BlueprintCallable, meta = (Keywords = "XhNativeRegisterGrabMeshComps"), Category = "Xh")
	void XhRegisterGrabMeshComps(TArray<UStaticMeshComponent*> InXhGrabMeshComps);
	//注册GrabMeshComponent
	UFUNCTION(BlueprintCallable, meta = (Keywords = "XhNativeRegisterGrabMeshComp"), Category = "Xh")
	void XhRegisterGrabMeshComp(UXhGrabMeshComponent* InXhGrabMeshComp);
	//抓取
	UFUNCTION(BlueprintCallable, meta = (Keywords = "XhGrab"), Category = "Xh")
	void XhGrab(UStaticMeshComponent* InMeshComp, USceneComponent* InAttchParent, EXhHand InHand = EXhHand::Max, const FName SocketName = NAME_None, float DelayAttch = 0);

	//扔下
	UFUNCTION(BlueprintCallable, meta = (Keywords = "XhDrop"), Category = "Xh")
	void XhDrop(UStaticMeshComponent* InMeshComp);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XhVar|Settings")
	bool bAutoInitGrab;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void InitGrab();
	virtual void XhNativeInit() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
