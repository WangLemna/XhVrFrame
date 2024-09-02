// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "XhType.generated.h"

#pragma region XhButton
/*间隔模式*/
UENUM(BlueprintType)
enum class EDuringMode : uint8
{
	DisableButton UMETA(DisplayName = "使整个Button不能用"),
	DisableClickEvent UMETA(DisplayName = "只取消Click事件")
};
#pragma endregion


//USTRUCT(BlueprintType)
//struct EKB_ControlObj
//{
//
//};

#pragma region XhTool
/*FileWriteType*/
UENUM(BlueprintType)
enum class FileWrite : uint8
{
	FILEWRITE_None,
	FILEWRITE_NoFail,
	FILEWRITE_NoReplaceExisting,
	FILEWRITE_EvenIfReadOnly,
	FILEWRITE_Append,
	FILEWRITE_AllowRead,
	FILEWRITE_Silent
};

/*FileMode*/
UENUM(BlueprintType)
enum class FileMode : uint8
{
	String,
	StringArray
};

#pragma endregion

#pragma region XhCharater
UENUM(BlueprintType)
enum class EKB_ControlObj : uint8
{
	None UMETA(DisplayName = "无"),
	L_Hand UMETA(DisplayName = "左手"),
	R_Hand UMETA(DisplayName = "右手"),
	Pawn UMETA(DisplayName = "玩家"),
};

UENUM(BlueprintType)
enum class EXhHand : uint8
{
	None UMETA(DisplayName = "无"),
	Left UMETA(DisplayName = "左手"),
	Right UMETA(DisplayName = "右手"),
	Max UMETA(DisplayName = "None"),
};
#pragma endregion

#pragma region XhWalk
UENUM(BlueprintType)
enum class EWalkTraceHitResult : uint8
{
	None,
	InRange,
	OutRange,
};
#pragma endregion

#pragma region XhTrace
UENUM(BlueprintType)
enum class EXhTraceMode : uint8
{
	Trace UMETA(DisplayName = "发射射线"),
	Widget UMETA(DisplayName = "UI射线"),
};
#pragma endregion

#pragma region XhGrab
UENUM(BlueprintType)
enum class EXhGrabEvent : uint8
{
	None UMETA(DisplayName = "未发生事件"),
	E_LeftOverlap_S UMETA(DisplayName = "左手触碰事件开始"),
	E_LeftOverlap_E UMETA(DisplayName = "左手触碰事件结束"),
	E_RightOverlap_S UMETA(DisplayName = "右手触碰事件开始"),
	E_RightOverlap_E UMETA(DisplayName = "右手触碰事件结束"),
	E_LeftGrab_S UMETA(DisplayName = "左手拿起事件开始"),
	E_LeftGrab_E UMETA(DisplayName = "左手拿起事件结束"),
	E_RightGrab_S UMETA(DisplayName = "右手拿起事件开始"),
	E_RightGrab_E UMETA(DisplayName = "右手拿起事件结束"),
	E_Drop UMETA(DisplayName = "扔下事件"),
	Max UMETA(DisplayName = "None"),
};

static FString EnumToString(EXhGrabEvent InValue)
{
#if WITH_EDITORONLY_DATA
	return FString::Printf(TEXT("%s"), *UEnum::GetDisplayValueAsText(InValue).ToString());
#endif
	FString Str;
	switch (InValue)
	{
	case EXhGrabEvent::None:
		Str = TEXT("未发生事件");
		break;
	case EXhGrabEvent::E_LeftOverlap_S:
		Str = TEXT("左手触碰事件开始");
		break;
	case EXhGrabEvent::E_LeftOverlap_E:
		Str = TEXT("左手触碰事件结束");
		break;
	case EXhGrabEvent::E_RightOverlap_S:
		Str = TEXT("右手触碰事件开始");
		break;
	case EXhGrabEvent::E_RightOverlap_E:
		Str = TEXT("右手触碰事件结束");
		break;
	case EXhGrabEvent::E_LeftGrab_S:
		Str = TEXT("左手拿起事件开始");
		break;
	case EXhGrabEvent::E_LeftGrab_E:
		Str = TEXT("左手拿起事件结束");
		break;
	case EXhGrabEvent::E_RightGrab_S:
		Str = TEXT("右手拿起事件开始");
		break;
	case EXhGrabEvent::E_RightGrab_E:
		Str = TEXT("右手拿起事件结束");
		break;
	case EXhGrabEvent::E_Drop:
		Str = TEXT("扔下事件");
		break;
	case EXhGrabEvent::Max:
		Str = TEXT("None");
		break;
	default:
		break;
	}
	return Str;
}

UENUM(BlueprintType)
enum class EXhGrabState : uint8
{
	None UMETA(DisplayName = "未触碰"),
	LeftOverlap UMETA(DisplayName = "左手已触碰"),
	RightOverlap UMETA(DisplayName = "右手已触碰"),
	AllOverlap UMETA(DisplayName = "左右手都已触碰"),
	LeftGrab UMETA(DisplayName = "左手已拿起"),
	RightGrab UMETA(DisplayName = "右手已拿起"),
	LeftGrabRightOverlap UMETA(DisplayName = "左手已拿起，右手已触碰"),
	RightGrabLeftOverlap UMETA(DisplayName = "右手已拿起，左手已触碰"),
	LeftGrabbing UMETA(DisplayName = "左手正在拿起中"),
	RightGrabbing UMETA(DisplayName = "右手正在拿起中"),
	Max UMETA(DisplayName = "None"),
};


static FString EnumToString(EXhGrabState InValue)
{
#if WITH_EDITORONLY_DATA
	return FString::Printf(TEXT("%s"), *UEnum::GetDisplayValueAsText(InValue).ToString());
#endif
	FString Str;
	switch (InValue)
	{
	case EXhGrabState::None:
		Str = TEXT("未触碰");
		break;
	case EXhGrabState::LeftOverlap:
		Str = TEXT("左手已触碰");
		break;
	case EXhGrabState::RightOverlap:
		Str = TEXT("右手已触碰");
		break;
	case EXhGrabState::AllOverlap:
		Str = TEXT("左右手都已触碰");
		break;
	case EXhGrabState::LeftGrab:
		Str = TEXT("左手已拿起");
		break;
	case EXhGrabState::RightGrab:
		Str = TEXT("右手已拿起");
		break;
	case EXhGrabState::LeftGrabRightOverlap:
		Str = TEXT("左手已拿起，右手已触碰");
		break;
	case EXhGrabState::RightGrabLeftOverlap:
		Str = TEXT("右手已拿起，左手已触碰");
		break;
	case EXhGrabState::LeftGrabbing:
		Str = TEXT("左手正在拿起中");
		break;
	case EXhGrabState::RightGrabbing:
		Str = TEXT("右手正在拿起中");
		break;
	case EXhGrabState::Max:
		Str = TEXT("None");
		break;
	default:
		break;
	}
	return Str;
}


USTRUCT(BlueprintType)
struct FGrabAndGrabEvent
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EXhGrabState GrabState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EXhGrabEvent GrabEvent;
	FGrabAndGrabEvent()
		: GrabState(EXhGrabState::None)
		, GrabEvent(EXhGrabEvent::None)
	{

	}
	FGrabAndGrabEvent(EXhGrabState InXhGrabState, EXhGrabEvent InXhHand)
		: GrabState(InXhGrabState)
		, GrabEvent(InXhHand)
	{

	}
	bool operator==(const FGrabAndGrabEvent B) const
	{
		return GrabState == B.GrabState && GrabEvent == B.GrabEvent;
	}
	friend inline int32 GetTypeHash(const FGrabAndGrabEvent& Key)
	{
		return HashCombine((uint32)Key.GrabState, (uint32)Key.GrabEvent);
	}
};
#pragma endregion

#pragma region XhAnswer
UENUM(BlueprintType)
enum class EQuestionType : uint8
{
	Multi UMETA(DisplayName = "多选"),
	One UMETA(DisplayName = "单选"),
};
USTRUCT(BlueprintType)
struct FTextContent
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = "true"))
	FText Content;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FontSize;
	FTextContent()
		:Content(FText::FromString(TEXT_EMPTY))
		,FontSize(24)
	{
	}
	FTextContent(FText InContent, int32 InFontSize)
		:Content(InContent)
		,FontSize(InFontSize)
	{
	}
};

USTRUCT(BlueprintType)
struct FXhSet
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<FString> XhSet;
};

USTRUCT(BlueprintType)
struct FButtonContent
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTextContent ButtonText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ButtonID;
	FButtonContent()
	{}
	FButtonContent(FTextContent InButtonText, FString InButtonID)
		:ButtonText(InButtonText)
		,ButtonID(InButtonID)
	{

	}
};
#pragma endregion


USTRUCT(BlueprintType)
struct FXhActorBaseArray
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AXhActorBase*> XhActorBaseArray;
	FXhActorBaseArray()
	{}
	FXhActorBaseArray(const TArray<AXhActorBase*>& InArray)
		:XhActorBaseArray(InArray)
	{}
};

UENUM(BlueprintType)
enum class EButtonEvent : uint8
{
	None,
	Pressed,
	Released,
	Max,
};

USTRUCT(BlueprintType)
struct FActorTransform : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform Transform;
	FActorTransform()
		:Name(TEXT(""))
		,Transform(FTransform())
	{}
	bool operator==(const FActorTransform B) const
	{
		return Name == B.Name && Transform.Equals(B.Transform,0.0001);
	}
};

//DataActorBaseStruct
USTRUCT(BlueprintType)
struct FDAB_Struct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AXhDataActorBase* DataActor;
	FDAB_Struct()
		:Description(TEXT(""))
		,DataActor(nullptr)
	{}
	bool operator==(const FDAB_Struct B) const
	{
		return Description == B.Description && DataActor == B.DataActor;
	}
};



#pragma region OculusEvent
UENUM(BlueprintType)
enum class EOculusEvent : uint8
{
	None,
	OculusA,
	OculusB,
	OculusX,
	OculusY,
	OculusJoystickL,
	OculusJoystickR,
	OculusGripL,
	OculusGripR,
	OculusTriggerL,
	OculusTriggerR,
	Max,
};

static FString EnumToString(EOculusEvent InValue)
{
#if WITH_EDITORONLY_DATA
	return FString::Printf(TEXT("%s"), *UEnum::GetDisplayValueAsText(InValue).ToString());
#endif
	FString Str;
	switch (InValue)
	{
	case EOculusEvent::None:
		Str = TEXT("None");
		break;
	case EOculusEvent::OculusA:
		Str = TEXT("OculusA");
		break;
	case EOculusEvent::OculusB:
		Str = TEXT("OculusB");
		break;
	case EOculusEvent::OculusX:
		Str = TEXT("OculusX");
		break;
	case EOculusEvent::OculusY:
		Str = TEXT("OculusY");
		break;
	case EOculusEvent::OculusJoystickL:
		Str = TEXT("OculusJoystickL");
		break;
	case EOculusEvent::OculusJoystickR:
		Str = TEXT("OculusJoystickR");
		break;
	case EOculusEvent::OculusGripL:
		Str = TEXT("OculusGripL");
		break;
	case EOculusEvent::OculusGripR:
		Str = TEXT("OculusGripR");
		break;
	case EOculusEvent::OculusTriggerL:
		Str = TEXT("OculusTriggerL");
		break;
	case EOculusEvent::OculusTriggerR:
		Str = TEXT("OculusTriggerR");
		break;
	case EOculusEvent::Max:
		Str = TEXT("Max");
		break;
	default:
		break;
	}
	return Str;
}

//
USTRUCT(BlueprintType)
struct FOculusEventMode
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EOculusEvent OculusEvent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EButtonEvent ButtonEvent;
	FOculusEventMode()
		:OculusEvent(EOculusEvent::Max)
		, ButtonEvent(EButtonEvent::Max)
	{}
	FOculusEventMode(EOculusEvent InOculusEvent, EButtonEvent InButtonEvent)
		:OculusEvent(InOculusEvent)
		, ButtonEvent(InButtonEvent)
	{}
	bool operator==(const FOculusEventMode B) const
	{
		return OculusEvent == B.OculusEvent && ButtonEvent == B.ButtonEvent;
	}

	bool IsValidData() const
	{
		return OculusEvent != EOculusEvent::None
			&& OculusEvent != EOculusEvent::Max
			&& ButtonEvent != EButtonEvent::None
			&& ButtonEvent != EButtonEvent::Max;
	}
	EXhHand GetHand() const
	{
		if (OculusEvent == EOculusEvent::None || ButtonEvent == EButtonEvent::Max)
		{
			return EXhHand::Max;
		}
		if (OculusEvent == EOculusEvent::OculusX
			|| OculusEvent == EOculusEvent::OculusY
			|| OculusEvent == EOculusEvent::OculusJoystickL
			|| OculusEvent == EOculusEvent::OculusGripL
			|| OculusEvent == EOculusEvent::OculusTriggerL)
		{
			return EXhHand::Left;
		}
		if (OculusEvent == EOculusEvent::OculusA
			|| OculusEvent == EOculusEvent::OculusB
			|| OculusEvent == EOculusEvent::OculusJoystickR
			|| OculusEvent == EOculusEvent::OculusGripR
			|| OculusEvent == EOculusEvent::OculusTriggerR)
		{
			return EXhHand::Right;
		}
		return EXhHand::Max;
	}
	friend inline int32 GetTypeHash(const FOculusEventMode& Key)
	{
		return HashCombine((uint32)Key.OculusEvent, (uint32)Key.ButtonEvent);
	}
};

#pragma endregion
// 
// //XhActorBaseStruct
// USTRUCT(BlueprintType)
// struct FXAB_Struct
// {
// 	GENERATED_USTRUCT_BODY()
// 
// public:
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	FString ID;
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	class AXhDataActorBase* DataActor;
// 	FXAB_Struct()
// 		:ID(TEXT(""))
// 		, DataActor(nullptr)
// 	{}
// 	FXAB_Struct(AXhDataActorBase* InDataActor)
// 		:ID(TEXT(""))
// 		, DataActor(InDataActor)
// 	{}
// 	FXAB_Struct(const FString& InID, AXhDataActorBase* InDataActor)
// 		:ID(InID)
// 		, DataActor(InDataActor)
// 	{}
// 	bool operator==(const FXAB_Struct B) const
// 	{
// 		return ID == B.ID && DataActor == B.DataActor;
// 	}
// };
