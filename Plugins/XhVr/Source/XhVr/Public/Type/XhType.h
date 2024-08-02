// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	L_Hand UMETA(DisplayName = "左手"),
	R_Hand UMETA(DisplayName = "右手"),
	Max UMETA(DisplayName = ""),
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

UENUM(BlueprintType)
enum class EXhTraceMode : uint8
{
	Trace UMETA(DisplayName = "发射射线"),
	Widget UMETA(DisplayName = "UI射线"),
};



UENUM(BlueprintType)
enum class EQuestionType : uint8
{
	Multi UMETA(DisplayName = "多选"),
	One UMETA(DisplayName = "单选"),
};

UENUM(BlueprintType)
enum class EXhGrabStateEvent : uint8
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

USTRUCT(BlueprintType)
struct FGrabAndHandState
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EXhGrabState GrabState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EXhGrabStateEvent HandState;
	FGrabAndHandState()
		: GrabState(EXhGrabState::None)
		, HandState(EXhGrabStateEvent::None)
	{

	}
	FGrabAndHandState(EXhGrabState InXhGrabState, EXhGrabStateEvent InXhHand)
		: GrabState(InXhGrabState)
		, HandState(InXhHand)
	{

	}
	bool operator==(const FGrabAndHandState B) const
	{
		return GrabState == B.GrabState && HandState == B.HandState;
	}
	friend inline int32 GetTypeHash(const FGrabAndHandState& Key)
	{
		return HashCombine((uint32)Key.GrabState, (uint32)Key.HandState);
	}
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

