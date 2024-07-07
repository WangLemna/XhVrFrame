// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XhArrowActorBase.generated.h"

class UWidgetComponent;

UCLASS()
class XHVR_API AXhArrowActorBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category = "ArrowActorBase", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> ArrowRoot;
	UPROPERTY(Category = "ArrowActorBase", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> ArrowMesh;
public:	
	// Sets default values for this actor's properties
	AXhArrowActorBase();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
