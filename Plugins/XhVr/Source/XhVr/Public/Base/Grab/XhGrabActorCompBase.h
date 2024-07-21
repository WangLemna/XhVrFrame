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


	//UFUNCTION(BlueprintImplementableEvent)
	//void XhBeginOverlap(const TArray<UStaticMeshComponent*>& InMeshComps);




public:
	TArray<UStaticMeshComponent*> GrabMeshComps;
	TMap<UStaticMeshComponent*, EXhGrabState> MeshCompsGrabState;
	TMap<UStaticMeshComponent*, EXhGrabState> MeshCompsLastGrabState;
	AXhCharacter* XhCharacter;
public:
	void XhNativeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void XhNativeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	EXhGrabState NextGrabeState(UStaticMeshComponent* InMeshComp, EXhGrabState InGrabState);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
