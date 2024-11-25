// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "XhGameState.generated.h"

class AXhGameMode;
class AXhCharacter;
class UXhGameInstance;
/**
 * 
 */
UCLASS()
class XHVR_API AXhGameState : public AGameState
{
	GENERATED_BODY()
public:
	AXhGameState();
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XhVar|Base")
	AXhGameMode* XhGameMode;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XhVar|Base")
	TMap<FString, FTransform> ActorsTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Debug")
	bool bDebug;
public:
	int32 XhBeginOrder;
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "GetXhActorTransform"))
	FTransform GetXhActorTransform(const FString& InName);
public:
	virtual void XhNativeInit();
protected:
	UFUNCTION(BlueprintImplementableEvent, meta = (Keywords = "XhBegin"))
	void XhBegin();
protected:
	/** Overridable native event for when play begins for this actor. */
	virtual void BeginPlay() override;
};
