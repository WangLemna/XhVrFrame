﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Type/XhCore.h"
#include "XhActorBase.generated.h"

class AXhGameState;
class AXhPlayerController;
class AXhPlayerState;
class AXhCharacter;
UCLASS()
class XHVR_API AXhActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXhActorBase();
public:
	int32 XhBeginOrder;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XhVar|Base")
	FString XhClassName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|BlueprintChange")
	AXhPlayerState* XhPlayerState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Setting", meta = (ExposeOnSpawn = "true"))
	FString XhActorId;


protected:
	bool bCanOpera;

public:
	//存在于场景中的start
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (Keywords = "XhStart"))
	void XhStart();

	//动画通知的XhManual
// 	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (Keywords = "XhManual"))
// 	void XhManual();

	//能否被操作
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "GetCanOpera"))
	bool GetCanOpera();

	//通过ID得到XhActorBase
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "GetXhActorById"))
	AXhActorBase* GetXhActorById(const FString& InId);

	//通过ClassName得到XhActorBase数组
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "GetXhActorsByClassName"))
	TArray<AXhActorBase*> GetXhActorsByClassName(const FString& InClassName);

	//改变操作状态
	UFUNCTION(BlueprintCallable, meta = (Keywords = "ChangeCanOpera"))
	void ChangeCanOpera(bool InCanOpera);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void XhDebug();
protected:
	UFUNCTION(BlueprintImplementableEvent, meta = (Keywords = "XhBegin"))
	void XhBegin();
protected:
	virtual void XhNativeInit();
	//void XhDestroyed(AActor* DestroyedActor);
public:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
