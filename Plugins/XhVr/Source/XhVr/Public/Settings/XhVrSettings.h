// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "XhVrSettings.generated.h"

//UENUM(BlueprintType)
//enum class EDuringMode : uint8
//{
//	DisableButton UMETA(DisplayName = "使整个Button不能用"),
//	DisableClickEvent UMETA(DisplayName = "只取消Click事件")
//};

//USTRUCT(BlueprintType)
//struct EKB_ControlObj
//{
//
//};

UCLASS(config = Engine)//
class XHVR_API UXhVrSettings : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(config, EditAnywhere, Category = "Settings")
	bool bEnableLog;
	UPROPERTY(config, EditAnywhere, Category = "Settings")
	FString LogPath;
	UPROPERTY(config, EditAnywhere, Category = "Settings")
	FString LogFileName;
	UPROPERTY(config, EditAnywhere, Category = "Settings")
	int64 MaxLogSize;
};

