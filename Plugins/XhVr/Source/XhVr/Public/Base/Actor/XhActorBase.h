// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Type/XhCore.h"
#include "XhActorBase.generated.h"

class UXhGrabActorCompBase;
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
	AXhGameState* XhGameState;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XhVar|Base")
	AXhPlayerController* XhPlayerController;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XhVar|Base")
	AXhPlayerState* XhPlayerState;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XhVar|Base")
	AXhCharacter* XhCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XhVar|Base")
	FString XhClassName;



protected:
	UXhGrabActorCompBase* GrabComp;
	bool bCanOpera;
public:

	UFUNCTION(BlueprintImplementableEvent, meta = (Keywords = "XhStart"))
	void XhStart();

	UFUNCTION(BlueprintCallable, meta = (Keywords = "XhGrab"))
	void XhGrab(UStaticMeshComponent* InMeshComp, USceneComponent* InAttchParent, EXhGrabStateEvent InGrabStateEvent = EXhGrabStateEvent::Max, const FName& SocketName = NAME_None, float DelayAttch = 0);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "GetCanOpera"))
	bool GetCanOpera();

	UFUNCTION(BlueprintCallable, meta = (Keywords = "ChangeCanOpera"))
	void ChangeCanOpera(bool InCanOpera);
protected:
	UFUNCTION(BlueprintImplementableEvent, meta = (Keywords = "XhBegin"))
	void XhBegin();
protected:
	void XhNativeInit();

public:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
