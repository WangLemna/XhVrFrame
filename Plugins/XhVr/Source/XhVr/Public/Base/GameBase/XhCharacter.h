// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Type/XhCore.h"
#include "Settings/XhVrSettings.h"
#include "XhCharacter.generated.h"

class UInputMappingContext;
class UCameraComponent;
class UMotionControllerComponent;
class USphereComponent;
class UUI_KB_ControlTip;
class UInputAction;
struct FInputActionValue;
class UXhWalkActorCompBase;
DECLARE_LOG_CATEGORY_EXTERN(XhCharacterLog, Log, All)
UCLASS()
class XHVR_API AXhCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(Category = "VrPlayer", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> XhRoot;
	UPROPERTY(Category= "VrPlayer", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> XhCamera;
	UPROPERTY(Category= "VrPlayer", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UMotionControllerComponent> LeftMotionController;
	UPROPERTY(Category = "VrPlayer", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMotionControllerComponent> RightMotionController;
	UPROPERTY(Category = "VrPlayer", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> LeftGrabCollision;
	UPROPERTY(Category = "VrPlayer", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> RightGrabCollision;
	UPROPERTY(Category = "VrPlayer", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> WalkChild;
	UPROPERTY(Category = "VrPlayer", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> TraceChild;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Input")
	UInputMappingContext* DefaultMappingContext;

public:
	// Sets default values for this character's properties
	AXhCharacter();
	void InitEnableKB();
	void InitWalk();
	void InitTrace();

	USphereComponent* GetGrabCollision(EXhHand XhHand);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
	void XhBegin();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable)
	void XhStartWalk();
	UFUNCTION(BlueprintCallable)
	void XhEndWalk();

	UFUNCTION(BlueprintCallable)
	void XhChangeWalkCompActors(const TArray<AActor*>& InInRangeWalkActors, const TArray<AActor*>& InOutRangeWalkActors, const TArray<AActor*>& InWalkIgnoreActors, bool bAdd = true);

	UFUNCTION(BlueprintCallable)
	void XhEnableTrace(bool InWidgetTraceEnable);
	UFUNCTION(BlueprintCallable)
	void XhDisableTrace();
	UFUNCTION(BlueprintCallable)
	void XhSetTraceMode(EXhTraceMode InTraceMode);

	UFUNCTION(BlueprintCallable)
	void XhChangeTraceCompActors(const TArray<AActor*>& InTraceIgnoreActors, bool bAdd = true);
	UFUNCTION(BlueprintCallable)
	void XhClickStarted();
	UFUNCTION(BlueprintCallable)
	void XhClickCompleted();

//public:
//	UXhVrSettings* XhVrSettings;

private:
	//UInputComponent* XhCharInputComp;
#pragma region Xh_KB
protected:
	void MoveX(const FInputActionValue& Value);
	void MoveY(const FInputActionValue& Value);
	void MoveZ(const FInputActionValue& Value);
	void TurnRotator(const FInputActionValue& Value);
	void TurnRotatorStartCompleted(const FInputActionValue& Value);
	void SwtichControlObj(const FInputActionValue& Value);
	void ResetHand(const FInputActionValue& Value);
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XhVar|Input")
	UInputAction* MoveXAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XhVar|Input")
	UInputAction* MoveYAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XhVar|Input")
	UInputAction* MoveZAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XhVar|Input")
	UInputAction* TurnRotatorAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XhVar|Input")
	UInputAction* SwtichControlObjAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XhVar|Input")
	UInputAction* ResetHandAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Keyboard")
	float KB_Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Keyboard")
	TSubclassOf<UUI_KB_ControlTip> UI_ControlTip;

	bool bEnableKB;
	EKB_ControlObj ControlObj;
	UUI_KB_ControlTip* WBP_ControlTip;
	float TurnRotatorValue;
#pragma endregion
public:



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Walk")
	EXhHand WalkHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Walk")
	TArray<AActor*> InRangeWalkActors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Walk")
	TArray<AActor*> OutRangeWalkActors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Walk")
	TArray<AActor*> WalkIgnoreActors;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Trace")
	EXhHand TraceHand;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XhVar|Trace")
	TArray<AActor*> TraceIgnoreActors;




};
