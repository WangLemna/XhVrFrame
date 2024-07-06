// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Type/XhType.h"
#include "XhTraceActorCompBase.generated.h"

class UWidgetInteractionComponent;

DECLARE_LOG_CATEGORY_EXTERN(XhTraceActorCompBaseLog, Log, All)
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class XHVR_API UXhTraceActorCompBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UXhTraceActorCompBase();

public:
	UFUNCTION()
	void ActivateEvent(UActorComponent* Component, bool bReset);
	UFUNCTION()
	void DeactivatedEvent(UActorComponent* Component);

	UFUNCTION(BlueprintCallable)
	void XhEnableTrace(bool InWidgetTraceEnable);
	UFUNCTION(BlueprintCallable)
	void XhDisableTrace();
	UFUNCTION(BlueprintCallable)
	void XhSetTraceMode(EXhTraceMode InTraceMode);

	//发射射线
	UFUNCTION(BlueprintNativeEvent)
	void XhSendTrace();

	//得到碰撞结果
	UFUNCTION(BlueprintNativeEvent)
	void XhGetHitResult(FHitResult& OutHit);

	//处理碰撞结果
	UFUNCTION()
	void XhHitResult(const FHitResult& InHit);

	//true碰撞结果
	UFUNCTION(BlueprintNativeEvent)
	void XhHitResultTrue(const FHitResult& InHit);

	//false碰撞结果
	UFUNCTION(BlueprintNativeEvent)
	void XhHitResultFalse(const FHitResult& InHit);

	UFUNCTION(BlueprintCallable)
	bool XhRegisterTraceActor(UStaticMeshComponent* InTrace, UStaticMeshComponent* InHitPoint, UArrowComponent* InArrow, UWidgetInteractionComponent* InWidgetTrace);

	inline bool IsRegisterCompleted() { return bRegisterCompleted; }
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
	void XhBegin();
	void InitTraceActor();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	bool bRegisterCompleted;
	bool bCanTick;
	bool bWidgetTraceEnable;
	UStaticMeshComponent* XhTrace;
	UStaticMeshComponent* XhHitPoint;
	UArrowComponent* XhArrow;
	UWidgetInteractionComponent* XhWidgetTrace;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XhTrace|BlueprintChange")
	TArray<AActor*> IgnoreActors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhTrace|Settings")
	FString ChildActorName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhTrace|Settings")
	float TraceDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhTrace|Settings")
	FVector2D TraceSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhTrace|Settings")
	float HitPointForwardDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhTrace|Settings")
	EXhTraceMode TraceMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhTrace|Settings")
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhTrace|Settings")
	TObjectPtr<UStaticMesh> TraceMeshStyle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhTrace|Settings")
	TObjectPtr<UStaticMesh> HitPointMeshStyle;
};
