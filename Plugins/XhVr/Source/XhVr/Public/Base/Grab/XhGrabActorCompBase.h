﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Type/XhCore.h"
#include "XhGrabActorCompBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class XHVR_API UXhGrabActorCompBase : public UActorComponent
{
	GENERATED_BODY()




public:	
	// Sets default values for this component's properties
	UXhGrabActorCompBase();
	
public:
	//注册抓取的mesh
	UFUNCTION(BlueprintCallable)
	void XhRegisterGrabMeshComp(UStaticMeshComponent* InMeshComp);
	//注册抓取的mesh
	UFUNCTION(BlueprintCallable)
	void XhRegisterGrabMeshComps(const TArray<UStaticMeshComponent*>& InMeshComps);
	//卸载抓取的mesh
	UFUNCTION(BlueprintCallable)
	void XhUnregisterGrabMeshComp(UStaticMeshComponent* InMeshComp);
	//卸载抓取的mesh
	UFUNCTION(BlueprintCallable)
	void XhUnregisterGrabMeshComps(const TArray<UStaticMeshComponent*>& InMeshComps);
	//设置抓取mesh的状态
	UFUNCTION(BlueprintCallable)
	void XhSetGrabMeshCompState(UStaticMeshComponent* InMeshComp, EXhGrabState InXhGrabState);
	//设置抓取mesh的状态
	UFUNCTION(BlueprintCallable)
	void XhSetGrabMeshCompsState(const TArray<UStaticMeshComponent*>& InMeshComps, EXhGrabState InXhGrabState);
	//得到抓取mesh的状态
	UFUNCTION(BlueprintCallable, BlueprintPure)
	EXhGrabState XhGetGrabMeshCompState(UStaticMeshComponent* InMeshComp);
	//得到抓取mesh的上一次状态
	UFUNCTION(BlueprintCallable, BlueprintPure)
	EXhGrabState XhGetGrabMeshCompLastState(UStaticMeshComponent* InMeshComp);
	//判断是否可抓取
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool XhCanGrab(UStaticMeshComponent* InMeshComp, EXhGrabStateEvent InGrabStateEvent = EXhGrabStateEvent::Max);

	//抓取
	UFUNCTION(BlueprintCallable, meta = (Keywords = "XhGrab"))
	void XhGrab(UStaticMeshComponent* InMeshComp, USceneComponent* InAttchParent, EXhHand InHand = EXhHand::Max, const FName SocketName = NAME_None, float DelayAttch = 0);

	//扔下
	UFUNCTION(BlueprintCallable, meta = (Keywords = "XhDrop"))
	void XhDrop(UStaticMeshComponent* InMeshComp);
	
	//
	UFUNCTION()
	void XhNativeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void XhNativeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:
	//下一个状态的Map，记录所有的状态事件
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FGrabAndHandState, EXhGrabState> NextGrabStateMap;
	//左手的碰撞体
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UPrimitiveComponent*> LeftGrabCollisionComps;
	//右手的碰撞体
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UPrimitiveComponent*> RightGrabCollisionComps;


public:
	//可抓取的Mesh
	TArray<UStaticMeshComponent*> GrabMeshComps;
	//可抓取Mesh的当前状态
	TMap<UStaticMeshComponent*, EXhGrabState> MeshCompsCurrentGrabState;
	//可抓取Mesh的上一个状态
	TMap<UStaticMeshComponent*, EXhGrabState> MeshCompsLastGrabState;
public:
	//抓取结束
	void XhGrabEnd(UStaticMeshComponent* InMeshComp, USceneComponent* InAttchParent, const FName SocketName);
	//将mesh变为下一个状态
	EXhGrabState NextGrabeState(UStaticMeshComponent* InMeshComp, FGrabAndHandState InGrabAndHandState);
	//获取mesh的下一个状态
	EXhGrabState GetNextGrabeState(FGrabAndHandState InGrabAndHandState);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
