// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XhWalkActorBase.generated.h"
class USplineComponent;
class UArrowComponent;
class USplineMeshComponent;
class UXhWalkActorCompBase;
UCLASS()
class XHVR_API AXhWalkActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXhWalkActorBase();

	void XhStartWalk();
	void XhEndWalk();
	void XhSetWalker(AActor* InWalker);
	void XhChangeActors(const TArray<AActor*>& InRangeWalkActors, const TArray<AActor*>& OutRangeWalkActors, const TArray<AActor*>& WalkIgnoreActors, bool bAdd = true);
	void XhSetSplineMeshStyle(UStaticMesh* InSplineMeshStyle);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
	void XhBegin();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



public:
	UPROPERTY(Category = "XhWalkActorBase", VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> WalkRoot;
	UPROPERTY(Category = "XhWalkActorBase", VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USplineComponent> TraceSpline;
	UPROPERTY(Category = "XhWalkActorBase", VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> EndLocation;
	UPROPERTY(Category = "XhWalkActorBase", VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> WalkArrow;
	UPROPERTY(Category = "XhWalkActorBase", VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UXhWalkActorCompBase> WalkActorCompBase;

public:
};
