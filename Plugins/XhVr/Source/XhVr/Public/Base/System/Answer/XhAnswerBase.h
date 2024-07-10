// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/XhWidgetActor.h"
#include "UI/XhButton.h"
#include "Base/Actor/XhDataActorBase.h"
#include "XhAnswerBase.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine))
	FText Content;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FontSize;
	FTextContent()
		:FontSize(24)
	{
	}
};

USTRUCT(BlueprintType)
struct FXhSet
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine))
	TSet<FString> XhSet;
};

USTRUCT(BlueprintType)
struct FButtonContent
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTextContent Content;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ButtonID;
};

USTRUCT(BlueprintType)
struct FQuesionLib
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTextContent Question;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FButtonContent> Buttons;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestionType QuestionType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FXhSet Answers;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AXhDataActorBase> ExtraData;
	FQuesionLib()
		:QuestionType(EQuestionType::One)
	{
	}
};
UCLASS()
class XHVR_API AXhAnswerBase : public AXhWidgetActor
{
	GENERATED_BODY()
};

