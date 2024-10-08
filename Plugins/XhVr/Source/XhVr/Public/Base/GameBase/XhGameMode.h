// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "XhGameMode.generated.h"

class UXhVrSettings;

/**
 * 
 */
UCLASS()
class XHVR_API AXhGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	AXhGameMode();
	void InitLog();
public:
	UXhVrSettings* XhVrSettings;
	int32 XhBeginOrder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Debug")
	bool bEnableKB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Debug")
	bool bDebug;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Settings")
	UDataTable* DT_ActorTransform;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Settings")
	//TArray<FActorTransform*> ActorTransform;
protected:
	UFUNCTION(BlueprintImplementableEvent, meta = (Keywords = "XhBegin"))
	void XhBegin();
protected:
	/** Overridable native event for when play begins for this actor. */
	virtual void BeginPlay() override;

};
