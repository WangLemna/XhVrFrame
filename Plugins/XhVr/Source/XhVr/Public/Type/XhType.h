// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

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

