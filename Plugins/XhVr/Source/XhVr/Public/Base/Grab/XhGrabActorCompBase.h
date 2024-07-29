// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Type/XhCore.h"
#include "XhGrabActorCompBase.generated.h"

class AXhCharacter;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class XHVR_API UXhGrabActorCompBase : public UActorComponent
{
	GENERATED_BODY()




public:	
	// Sets default values for this component's properties
	UXhGrabActorCompBase();
	
public:
	UFUNCTION(BlueprintCallable)
	void XhRegisterGrabMeshComp(UStaticMeshComponent* InMeshComp);
	UFUNCTION(BlueprintCallable)
	void XhRegisterGrabMeshComps(const TArray<UStaticMeshComponent*>& InMeshComps);
	UFUNCTION(BlueprintCallable)
	void XhUnregisterGrabMeshComp(UStaticMeshComponent* InMeshComp);
	UFUNCTION(BlueprintCallable)
	void XhUnregisterGrabMeshComps(const TArray<UStaticMeshComponent*>& InMeshComps);

	UFUNCTION(BlueprintCallable)
	void XhSetGrabMeshCompState(UStaticMeshComponent* InMeshComp, EXhGrabState InXhGrabState);
	UFUNCTION(BlueprintCallable)
	void XhSetGrabMeshCompsState(const TArray<UStaticMeshComponent*>& InMeshComps, EXhGrabState InXhGrabState);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	EXhGrabState XhGetGrabMeshCompState(UStaticMeshComponent* InMeshComp);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool XhCanGrab(UStaticMeshComponent* InMeshComp);

	UFUNCTION(BlueprintCallable)
	void XhGrab(UStaticMeshComponent* InMeshComp, USceneComponent* AttchParent);

public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<EXhGrabState> CanGrabState;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FGrabAndHandState, EXhGrabState> NextGrabStateMap;


public:
	AXhCharacter* XhCharacter;
	TArray<UStaticMeshComponent*> GrabMeshComps;
	TMap<UStaticMeshComponent*, EXhGrabState> MeshCompsCurrentGrabState;
	TMap<UStaticMeshComponent*, EXhGrabState> MeshCompsLastGrabState;
public:
	void XhNativeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void XhNativeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	EXhGrabState NextGrabeState(UStaticMeshComponent* InMeshComp, FGrabAndHandState InGrabAndHandState);

	EXhGrabState GetNextGrabeState(FGrabAndHandState InGrabAndHandState);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
