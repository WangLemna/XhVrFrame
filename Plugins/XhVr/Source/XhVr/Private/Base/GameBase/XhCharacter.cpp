// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/GameBase/XhCharacter.h"
#include "Base/UMG/UI_KB_ControlTip.h"
#include "Base/Walk/XhWalkActorBase.h"
#include "Base/Trace/XhTraceActorBase.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "GenericPlatform/GenericPlatformProcess.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/TextBlock.h"
#include "Misc/Paths.h"

//#include "Components/SceneComponent.h"

DEFINE_LOG_CATEGORY(XhCharacterLog)
// Sets default values
AXhCharacter::AXhCharacter()
//	: Super(ObjectInitializer) const FObjectInitializer& ObjectInitializer
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	XhRoot = CreateDefaultSubobject<USceneComponent>(TEXT("XhRoot"));
	XhCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("XhCamera"));
	LeftMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftMotionController"));
	RightMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightMotionController"));
	LeftGrabCollision = CreateDefaultSubobject<USphereComponent>(TEXT("LeftGrabCollision"));
	RightGrabCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RightGrabCollision"));
	WalkChild = CreateDefaultSubobject<UChildActorComponent>(TEXT("WalkChild"));
	TraceChild = CreateDefaultSubobject<UChildActorComponent>(TEXT("TraceChild"));

	XhRoot->SetupAttachment(RootComponent);
	WalkChild->SetupAttachment(XhRoot);
	TraceChild->SetupAttachment(XhRoot);
	RightMotionController->SetupAttachment(XhRoot);
	RightGrabCollision->SetupAttachment(RightMotionController);
	LeftMotionController->SetupAttachment(XhRoot);
	LeftGrabCollision->SetupAttachment(LeftMotionController);
	XhCamera->SetupAttachment(XhRoot);


	WalkChild->SetChildActorClass(AXhWalkActorBase::StaticClass());
	TraceChild->SetChildActorClass(AXhTraceActorBase::StaticClass());

	XhRoot->SetRelativeLocation(FVector(0,0,-88));
	XhRoot->SetMobility(EComponentMobility::Movable);

	LeftMotionController->MotionSource = IMotionController::LeftHandSourceId;//FName(TEXT("Left"))

	LeftGrabCollision->SetRelativeScale3D(FVector(0.2));
	LeftGrabCollision->SetMobility(EComponentMobility::Movable);

	RightMotionController->MotionSource = IMotionController::RightHandSourceId;//FName(TEXT("Right"))

	RightGrabCollision->SetRelativeScale3D(FVector(0.2));
	RightGrabCollision->SetMobility(EComponentMobility::Movable);

	bUseControllerRotationYaw = false;


	WalkHand = EXhHand::Left;
	TraceHand = EXhHand::Left;
	KB_Speed = 1.f;
	ControlObj = EKB_ControlObj::Pawn;
	//UI_ControlTip = Cast<UUserWidget>(StaticLoadObject(UObject::StaticClass(), nullptr, TEXT("/Game/Path/To/YourAsset.YourAsset")));
}

void AXhCharacter::InitEnableKB()
{
	bEnableKB = true;
	LeftMotionController->PlayerIndex = -1.f;//SetAssociatedPlayerIndex
	RightMotionController->PlayerIndex = -1.f;
	if (UI_ControlTip)
	{
		WBP_ControlTip = CreateWidget<UUI_KB_ControlTip>(GetWorld(), UI_ControlTip);
		WBP_ControlTip->AddToPlayerScreen(-5.f);
	}
	//UKismetSystemLibrary::Delay(this, 0.2, FLatentActionInfo());
	XhCamera->SetRelativeLocation(FVector(0, 0, 170.f));
	LeftMotionController->SetRelativeLocation(FVector(75.f, -25.f, 150.f));
	RightMotionController->SetRelativeLocation(FVector(75.f, 25.f, 150.f));
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		PlayerController->SetShowMouseCursor(true);
	}
}

void AXhCharacter::InitWalk()
{
	UMotionControllerComponent* WalkAttach = nullptr;
	switch (WalkHand)
	{
	case EXhHand::None:
	break;
	case EXhHand::Left:
	{
		WalkAttach = LeftMotionController;
	}
	break;
	case EXhHand::Right:
	{
		WalkAttach = RightMotionController;
	}
	break;
	default:
		break;
	}
	if (WalkAttach)
	{
		FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
		WalkChild->AttachToComponent(WalkAttach, AttachmentTransformRules);
		AXhWalkActorBase* WalkActor = Cast<AXhWalkActorBase>(WalkChild->GetChildActor());
		if (WalkActor)
		{
			WalkActor->XhSetWalker(this);
			XhChangeWalkCompActors(InRangeWalkActors, OutRangeWalkActors, WalkIgnoreActors);
		}
	}
	else
	{
		WalkChild->DestroyChildActor();
		WalkChild->DestroyComponent();
	}
}

void AXhCharacter::InitTrace()
{
	UMotionControllerComponent* TraceAttach = nullptr;
	switch (TraceHand)
	{
	case EXhHand::None:
	break;
	case EXhHand::Left:
	{
		TraceAttach = LeftMotionController;
	}
	break;
	case EXhHand::Right:
	{
		TraceAttach = RightMotionController;
	}
	break;
	default:
		break;
	}
	if (TraceAttach)
	{
		FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
		TraceChild->AttachToComponent(TraceAttach, AttachmentTransformRules);
		AXhTraceActorBase* TraceActor = Cast<AXhTraceActorBase>(TraceChild->GetChildActor());
		if (TraceActor)
		{
			TraceActor->XhRegisterTraceActor();
			XhChangeTraceCompActors(TraceIgnoreActors);
		}
	}
	else
	{
		TraceChild->DestroyChildActor();
		TraceChild->DestroyComponent();
	}
}

USphereComponent* AXhCharacter::GetGrabCollision(EXhHand XhHand)
{
	USphereComponent* CollisionComponent = nullptr;
	switch (XhHand)
	{
	case EXhHand::None:
		break;
	case EXhHand::Left:
		CollisionComponent = LeftGrabCollision;
		break;
	case EXhHand::Right:
		CollisionComponent = RightGrabCollision;
		break;
	default:
		break;
	}
	return CollisionComponent;
}

// Called when the game starts or when spawned
void AXhCharacter::BeginPlay()
{
	Super::BeginPlay();
	//输入
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		PlayerController->EnableInput(PlayerController);
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	//行走
	InitWalk();
	//射线
	InitTrace();
	XhBegin();
}

// Called every frame
void AXhCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AXhCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	//XhCharInputComp = PlayerInputComponent;
	PlayerInputComponent->AxisKeyBindings.Add(FInputAxisKeyBinding(EKeys::MouseX));
	PlayerInputComponent->AxisKeyBindings.Add(FInputAxisKeyBinding(EKeys::MouseY));
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveXAction, ETriggerEvent::Triggered, this, &AXhCharacter::MoveX);
		EnhancedInputComponent->BindAction(MoveYAction, ETriggerEvent::Triggered, this, &AXhCharacter::MoveY);
		EnhancedInputComponent->BindAction(MoveZAction, ETriggerEvent::Triggered, this, &AXhCharacter::MoveZ);
		EnhancedInputComponent->BindAction(TurnRotatorAction, ETriggerEvent::Triggered, this, &AXhCharacter::TurnRotator);
		EnhancedInputComponent->BindAction(TurnRotatorAction, ETriggerEvent::Started, this, &AXhCharacter::TurnRotatorStartCompleted);
		EnhancedInputComponent->BindAction(TurnRotatorAction, ETriggerEvent::Completed, this, &AXhCharacter::TurnRotatorStartCompleted);
		EnhancedInputComponent->BindAction(SwtichControlObjAction, ETriggerEvent::Started, this, &AXhCharacter::SwtichControlObj);
		EnhancedInputComponent->BindAction(ResetHandAction, ETriggerEvent::Started, this, &AXhCharacter::ResetHand);
	}
	else
	{
		UE_LOG(XhCharacterLog, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}



void AXhCharacter::XhStartWalk()
{
	if (WalkChild)
	{
		AXhWalkActorBase* WalkActor = Cast<AXhWalkActorBase>(WalkChild->GetChildActor());
		if (WalkActor)
		{
			WalkActor->XhStartWalk();
		}
	}
}

void AXhCharacter::XhEndWalk()
{
	if (WalkChild)
	{
		AXhWalkActorBase* WalkActor = Cast<AXhWalkActorBase>(WalkChild->GetChildActor());
		if (WalkActor)
		{
			WalkActor->XhEndWalk();
		}
	}
}



void AXhCharacter::XhChangeWalkCompActors(const TArray<AActor*>& InInRangeWalkActors, const TArray<AActor*>& InOutRangeWalkActors, const TArray<AActor*>& InWalkIgnoreActors, bool bAdd /*= true*/)
{
	if (WalkChild)
	{
		AXhWalkActorBase* WalkActor = Cast<AXhWalkActorBase>(WalkChild->GetChildActor());
		if (WalkActor)
		{
			WalkActor->XhChangeActors(InInRangeWalkActors, InOutRangeWalkActors, InWalkIgnoreActors, bAdd);
		}
	}
}

void AXhCharacter::XhEnableTrace(bool InWidgetTraceEnable)
{
	if (TraceChild)
	{
		AXhTraceActorBase* TraceActor = Cast<AXhTraceActorBase>(TraceChild->GetChildActor());
		if (TraceActor)
		{
			TraceActor->XhEnableTrace(InWidgetTraceEnable);
		}
	}
}

void AXhCharacter::XhDisableTrace()
{
	if (TraceChild)
	{
		AXhTraceActorBase* TraceActor = Cast<AXhTraceActorBase>(TraceChild->GetChildActor());
		if (TraceActor)
		{
			TraceActor->XhDisableTrace();
		}
	}
}

void AXhCharacter::XhSetTraceMode(EXhTraceMode InTraceMode)
{
	if (TraceChild)
	{
		AXhTraceActorBase* TraceActor = Cast<AXhTraceActorBase>(TraceChild->GetChildActor());
		if (TraceActor)
		{
			TraceActor->XhSetTraceMode(InTraceMode);
		}
	}
}

void AXhCharacter::XhChangeTraceCompActors(const TArray<AActor*>& InTraceIgnoreActors, bool bAdd /*= true*/)
{
	if (TraceChild)
	{
		AXhTraceActorBase* TraceActor = Cast<AXhTraceActorBase>(TraceChild->GetChildActor());
		if (TraceActor)
		{
			TraceActor->XhChangeActors(InTraceIgnoreActors, bAdd);
		}
	}
}

void AXhCharacter::XhClickStarted()
{
	if (TraceChild)
	{
		AXhTraceActorBase* TraceActor = Cast<AXhTraceActorBase>(TraceChild->GetChildActor());
		if (TraceActor)
		{
			TraceActor->XhClickStarted();
		}
	}
}

void AXhCharacter::XhClickCompleted()
{
	if (TraceChild)
	{
		AXhTraceActorBase* TraceActor = Cast<AXhTraceActorBase>(TraceChild->GetChildActor());
		if (TraceActor)
		{
			TraceActor->XhClickCompleted();
		}
	}
}

void AXhCharacter::MoveX(const FInputActionValue& Value)
{
	if (bEnableKB)
	{
		FVector AddLocation = GetActorForwardVector() * Value[0] * KB_Speed * TurnRotatorValue;
		switch (ControlObj)
		{
		case EKB_ControlObj::None:
			break;
		case EKB_ControlObj::L_Hand:
			LeftMotionController->AddWorldOffset(AddLocation);
			break;
		case EKB_ControlObj::R_Hand:
			RightMotionController->AddWorldOffset(AddLocation);
			break;
		case EKB_ControlObj::Pawn:
			AddActorWorldOffset(AddLocation);
			break;
		default:
			break;
		}
	}
}

void AXhCharacter::MoveY(const FInputActionValue& Value)
{
	if (bEnableKB)
	{
		FVector AddLocation = GetActorRightVector() * Value[0] * KB_Speed * TurnRotatorValue;
		switch (ControlObj)
		{
		case EKB_ControlObj::None:
			break;
		case EKB_ControlObj::L_Hand:
			LeftMotionController->AddWorldOffset(AddLocation);
			break;
		case EKB_ControlObj::R_Hand:
			RightMotionController->AddWorldOffset(AddLocation);
			break;
		case EKB_ControlObj::Pawn:
			AddActorWorldOffset(AddLocation);
			break;
		default:
			break;
		}
	}
}

void AXhCharacter::MoveZ(const FInputActionValue& Value)
{
	if (bEnableKB)
	{
		FVector AddLocation = GetActorUpVector() * Value[0] * KB_Speed * TurnRotatorValue;
		switch (ControlObj)
		{
		case EKB_ControlObj::None:
			break;
		case EKB_ControlObj::L_Hand:
			LeftMotionController->AddWorldOffset(AddLocation);
			break;
		case EKB_ControlObj::R_Hand:
			RightMotionController->AddWorldOffset(AddLocation);
			break;
		case EKB_ControlObj::Pawn:
			XhRoot->AddWorldOffset(AddLocation);
			break;
		default:
			break;
		}
	}
}

void AXhCharacter::TurnRotator(const FInputActionValue& Value)
{
	if (bEnableKB)
	{
		//TurnRotatorValue = Value[0];
		float RotatorPitch = GetInputAxisKeyValue(EKeys::MouseY) * KB_Speed * Value[0];
		float RotatorYaw = GetInputAxisKeyValue(EKeys::MouseX) * KB_Speed * Value[0];
		switch (ControlObj)
		{
		case EKB_ControlObj::None:
			break;
		case EKB_ControlObj::L_Hand:
			break;
		case EKB_ControlObj::R_Hand:
			break;
		case EKB_ControlObj::Pawn:
			AddActorLocalRotation(FRotator(RotatorPitch, 0, 0));
			AddActorLocalRotation(FRotator(0, RotatorYaw, 0));
			SetActorRotation(FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw, 0));
			break;
		default:
			break;
		}
	}
}

void AXhCharacter::TurnRotatorStartCompleted(const FInputActionValue& Value)
{
	TurnRotatorValue = Value[0];
}

void AXhCharacter::SwtichControlObj(const FInputActionValue& Value)
{
	if (bEnableKB)
	{
		FText ControlObjText;
		switch (ControlObj)
		{
		case EKB_ControlObj::None:
			ControlObj = EKB_ControlObj::Pawn;
			ControlObjText = FText::FromString(TEXT("玩家(相机)"));
			break;
		case EKB_ControlObj::L_Hand:
			ControlObj = EKB_ControlObj::R_Hand;
			ControlObjText = FText::FromString(TEXT("右手"));
			break;
		case EKB_ControlObj::R_Hand:
			ControlObj = EKB_ControlObj::None;
			ControlObjText = FText::FromString(TEXT("无"));
			break;
		case EKB_ControlObj::Pawn:
			ControlObj = EKB_ControlObj::L_Hand;
			ControlObjText = FText::FromString(TEXT("左手"));
			break;
		default:
			break;
		}
		WBP_ControlTip->ControlObj->SetText(ControlObjText);
	}
}

void AXhCharacter::ResetHand(const FInputActionValue& Value)
{
	if (bEnableKB)
	{
		switch (ControlObj)
		{
		case EKB_ControlObj::None:
			break;
		case EKB_ControlObj::L_Hand:
			LeftMotionController->SetRelativeLocation(FVector(75.f, -25.f, 150.f));
			break;
		case EKB_ControlObj::R_Hand:
			RightMotionController->SetRelativeLocation(FVector(75.f, 25.f, 150.f));
			break;
		case EKB_ControlObj::Pawn:
			LeftMotionController->SetRelativeLocation(FVector(75.f, -25.f, 150.f));
			RightMotionController->SetRelativeLocation(FVector(75.f, 25.f, 150.f));
			break;
		default:
			break;
		}
	}
}


