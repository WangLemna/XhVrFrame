// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Type/XhCore.h"
#include "XhGrabMeshComponent.generated.h"

class UXhGrabActorCompBase;
enum EXhGrabMeshCompnentEventType
{
	None,
	Grab,
	Drop,
	Max,
};

/** Delegate for notification of start of overlap with a specific component */
//DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_SixParams(FComponentBeginOverlapSignature, UPrimitiveComponent, OnComponentBeginOverlap, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult&, SweepResult);
/** Delegate for notification of end of overlap with a specific component */
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams(FComponentGrabSignature, UXhGrabMeshComponent, OnComponentGrab, USceneComponent*, InAttchParent, float, InDelayAttach);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FComponentDropSignature, UXhGrabMeshComponent, OnComponentDrop, USceneComponent*, InAttchParent);

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (Rendering, Common), hidecategories = (Object, Activation, "Components|Activation"), ShowCategories = (Mobility), editinlinenew, meta = (BlueprintSpawnableComponent))
class XHVR_API UXhGrabMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Settings")
	bool bAutoXhRegister;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Settings|Grab")
	FOculusEventMode GrabOculusEventMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Settings|Grab")
	USceneComponent* AttchParent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Settings|Grab")
	FName SocketName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Settings|Grab")
	float DelayAttach;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Settings|Drop")
	FOculusEventMode DropOculusEventMode;
	UPROPERTY(BlueprintAssignable, Category = "XhDelegate")
	FComponentGrabSignature OnComponentGrab;
	UPROPERTY(BlueprintAssignable, Category = "XhDelegate")
	FComponentDropSignature OnComponentDrop;

protected:
	TMap<FOculusEventMode, TArray<EXhGrabMeshCompnentEventType>> DelegateEventsMap;

public:
	UXhGrabMeshComponent(const FObjectInitializer& ObjectInitializer);
	//ץȡ
	//UFUNCTION(BlueprintCallable, meta = (Keywords = "XhGrab"), Category = "Xh")
	void XhDelegateEvents(FOculusEventMode InOculusEventMode, UXhGrabActorCompBase* GrabComp);

public:
	void XhNativeInit();
	TArray<FOculusEventMode> GetOculusEvents();
	//UPROPERTY(BlueprintAssignable, Category = "Collision")
	//FComponentBeginOverlapSignature OnComponentBeginOverlap;
protected:
	virtual void BeginPlay() override;
};
