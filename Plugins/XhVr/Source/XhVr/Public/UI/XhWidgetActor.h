// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UI/XhButton.h"
#include "Base/Actor/XhActorBase.h"
#include "XhWidgetActor.generated.h"

UCLASS()
class XHVR_API AXhWidgetActor : public AXhActorBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXhWidgetActor();

	void Init();
public:
	int32 XhBeginOrder;
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (Keywords = "XhClick", DisplayName = "XhClick"))//BlueprintImplementableEvent
	void XhClicked(const FString& ButtonID, UXhButton* Button);//UPARAM(ref)

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (Keywords = "XhUnHover", DisplayName = "XhUnHover"))
	void XhUnHovered(const FString& ButtonID, UXhButton* Button);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (Keywords = "XhHover", DisplayName = "XhHover"))
	void XhHovered(const FString& ButtonID, UXhButton* Button);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (Keywords = "XhUnHover", DisplayName = "XhPressed"))
	void XhPressed(const FString& ButtonID, UXhButton* Button);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (Keywords = "XhUnHover", DisplayName = "XhReleased"))
	void XhReleased(const FString& ButtonID, UXhButton* Button);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
