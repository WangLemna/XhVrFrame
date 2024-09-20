// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UI/XhButton.h"
#include "Type/XhCore.h"
#include "Base/Actor/XhDataActorBase.h"
#include "Base/Actor/XhActorBase.h"
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
	FDAB_Struct ExtraData;
	FQuesionLib()
		:QuestionType(EQuestionType::One)
		,ExtraData(FDAB_Struct())
	{
	}
};

UCLASS()
class XHVR_API AXhAnswerSystemBase : public AXhActorBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXhAnswerSystemBase();
public:
	int32 XhBeginOrder;
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
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void NextQuestion();
	UFUNCTION(BlueprintCallable)
	bool InitData();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	TArray<int32> GetErrorQuestionsIndex();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetErrorQuestionsCount();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<FText> GetErrorQuestions();
	UFUNCTION(BlueprintImplementableEvent)
	void XhAnswerFinish();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
