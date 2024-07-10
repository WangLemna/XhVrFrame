// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/XhWidgetActor.h"
#include "UI/XhButton.h"
#include "XhAnswerBase.generated.h"

UENUM(BlueprintType)
enum class EQuestionType : uint8
{
	Multi UMETA(DisplayName = "多选"),
	One UMETA(DisplayName = "单选"),
};

UCLASS()
class XHVR_API AXhAnswerBase : public AXhWidgetActor
{
	GENERATED_BODY()
};

