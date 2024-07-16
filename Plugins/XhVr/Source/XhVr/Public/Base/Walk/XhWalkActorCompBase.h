// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Type/XhCore.h"
#include "XhWalkActorCompBase.generated.h"

class UArrowComponent;
class USplineComponent;
class USplineMeshComponent;
DECLARE_LOG_CATEGORY_EXTERN(XhWalkActorCompBaseLog, Log, All)
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class XHVR_API UXhWalkActorCompBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UXhWalkActorCompBase();
public:
	UFUNCTION()
	void ActivateEvent(UActorComponent* Component, bool bReset);
	UFUNCTION()
	void DeactivatedEvent(UActorComponent* Component);

	UFUNCTION(BlueprintCallable)
	void XhStartWalk();
	UFUNCTION(BlueprintCallable)
	void XhEndWalk();

	UFUNCTION(BlueprintNativeEvent)
	void XhWalk();

	//清除样条线模型
	UFUNCTION(BlueprintNativeEvent)
	void XhClearSpline();
	//发射样条线
	UFUNCTION(BlueprintNativeEvent)
	bool XhSendSpline(FHitResult& OutHit, TArray<FVector>& OutPathPositions, FVector& OutLastTraceDestination);
	//处理行走状态结果
	UFUNCTION(BlueprintNativeEvent)
	bool XhGetWalkStateResult(FHitResult InHit, bool InHitResult, EWalkTraceHitResult& OutWalkState);
	

	UFUNCTION()
	void XhMakeSplineMesh(EWalkTraceHitResult InWalkState, TArray<FVector> InPathPositions);
	UFUNCTION(BlueprintNativeEvent)
	void XhMakeSplineMeshNone(const TArray<FVector>& InPathPositions);
	UFUNCTION(BlueprintNativeEvent)
	void XhMakeSplineMeshInRange(const TArray<FVector>& InPathPositions);
	UFUNCTION(BlueprintNativeEvent)
	void XhMakeSplineMeshOutRange(const TArray<FVector>& InPathPositions);


	UFUNCTION()
	void XhUpdateEndMesh(EWalkTraceHitResult InWalkState, FVector InLastTraceDestination);
	UFUNCTION(BlueprintNativeEvent)
	void XhUpdateEndMeshNone(FVector InLastTraceDestination);
	UFUNCTION(BlueprintNativeEvent)
	void XhUpdateEndMeshInRange(FVector InLastTraceDestination);
	UFUNCTION(BlueprintNativeEvent)
	void XhUpdateEndMeshOutRange(FVector InLastTraceDestination);


	UFUNCTION(BlueprintNativeEvent)
	void XhOverWalk();


	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	void XhGetWalkLocarionAndRotation(FVector& OutLocation, FRotator& OutRotation);

	UFUNCTION(BlueprintNativeEvent)
	void XhClearWalk();

	UFUNCTION(BlueprintCallable)
	bool XhRegisterWalkActor(AActor* InWalker, USplineComponent* InTraceSpline, UArrowComponent* InWalkArrow, UStaticMeshComponent* InEndLocation);

	UFUNCTION(BlueprintCallable)
	void XhPrint();
	
	inline bool IsRegisterCompleted() { return bRegisterCompleted; }
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
	void XhBegin();
	void InitWalkActor();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;





protected:
	bool bRegisterCompleted;
	bool bStartWalk;
	bool bIsWalking;
	bool bCanTick;
	//AActor* XhParent;
	AActor* XhWalker;
	USplineComponent* TraceSpline;
	UStaticMeshComponent* WalkEnd;
	FVector EndInitLocation;
	FRotator EndInitRotation;
	UArrowComponent* WalkArrow;
	TArray<USplineMeshComponent*> SplineMeshes;

	FVector FinalWalkLocation;
	FRotator FinalWalkRotation;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhWalk|BlueprintChange")
	TArray<AActor*> InRangeWalkActors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhWalk|BlueprintChange")
	TArray<AActor*> OutRangeWalkActors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhWalk|BlueprintChange")
	TArray<AActor*> IgnoreActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhWalk|BlueprintChange")
	bool bValidSpline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhWalk|BlueprintChange")
	float WalkRotationYaw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhWalk|BlueprintChange")
	FVector WalkLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhWalk|Settings")
	FString ChildActorName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhWalk|Settings")
	bool bIsDot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhWalk|Settings")
	float SimFrequency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhWalk|Settings")
	float WalkDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhWalk|Settings")
	float FadeInDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhWalk|Settings")
	float FadeOutDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhWalk|Settings")
	FLinearColor FadeColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhWalk|Settings")
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhWalk|Settings")
	TObjectPtr<UStaticMesh> SplineMeshStyle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhWalk|Settings")
	float InitailLocationZ;






};
