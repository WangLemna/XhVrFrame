// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UI/XhButton.h"
#include "Type/XhCore.h"
#include "Base/Actor/XhDataActorBase.h"
#include "XhAnswerSystemBase.generated.h"

class AXhAnswerBase;

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
	FXhSet Answer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AXhDataActorBase* ExtraData;
	FQuesionLib()
		:QuestionType(EQuestionType::One)
		,ExtraData(nullptr)
	{
	}
};

UCLASS()
class XHVR_API AXhAnswerSystemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXhAnswerSystemBase();

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "XhVar|Settings")
	TArray<FQuesionLib> QuestionLibs;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Settings")
	TSubclassOf<AXhAnswerBase> AnswerActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Settings")
	FTransform AnswerActorTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|BlueprintChange")
	int32 QuestionIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|BlueprintChange")
	TMap<int32, FXhSet> Answers;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|BlueprintChange")
	TMap<int32, FXhSet> Selects;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	UFUNCTION(BlueprintImplementableEvent)
	void XhBegin();
	UFUNCTION(BlueprintNativeEvent)
	void NextQuestion();
	bool InitData();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
