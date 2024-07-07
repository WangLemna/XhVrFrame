// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Type/XhCore.h"
#include "XhTraceActorBase.generated.h"

class UArrowComponent;
class UWidgetInteractionComponent;
class UXhTraceActorCompBase;

UCLASS()
class XHVR_API AXhTraceActorBase : public AActor
{
	GENERATED_BODY()
	

public:
	UPROPERTY(Category = "TraceActorBase", VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> TraceRoot;
	UPROPERTY(Category = "TraceActorBase", VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> XhTrace;
	UPROPERTY(Category = "TraceActorBase", VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> XhHitPoint;
	UPROPERTY(Category = "TraceActorBase", VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> TraceArrow;
	UPROPERTY(Category = "TraceActorBase", VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UWidgetInteractionComponent> WidgetTrace;
	UPROPERTY(Category = "TraceActorBase", VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UXhTraceActorCompBase> TraceActorCompBase;


public:	
	// Sets default values for this actor's properties
	AXhTraceActorBase();
	void XhEnableTrace(bool InWidgetTraceEnable);
	void XhDisableTrace();
	void XhSetTraceMode(EXhTraceMode InTraceMode);
	void XhRegisterTraceActor();
	void XhChangeActors(const TArray<AActor*>& TraceIgnoreActors, bool bAdd = true);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//UFUNCTION(BlueprintImplementableEvent)
	//void XhBegin();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
