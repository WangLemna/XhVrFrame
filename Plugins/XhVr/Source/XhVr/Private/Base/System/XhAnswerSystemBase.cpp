// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/System/XhAnswerSystemBase.h"
#include "Base/System/Answer/XhAnswerBase.h"

// Sets default values
AXhAnswerSystemBase::AXhAnswerSystemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AXhAnswerSystemBase::BeginPlay()
{
	Super::BeginPlay();
	if (InitData())
	{
		NextQuestion();
	}
}

void AXhAnswerSystemBase::NextQuestion_Implementation()
{
	if (QuestionLib.IsValidIndex(QuestionIndex))
	{
		if (AnswerActor)
		{
			GetWorld()->SpawnActor<AXhAnswerBase>();
			QuestionIndex++;
		}
		else
		{
			UXhTool::WriteLog(this, TEXT("NextQuestion:AnswerActor无效"));
		}
	}
	else
	{
		//
	}
}

bool AXhAnswerSystemBase::InitData()
{
	int32 Length = QuestionLib.Num();
	for (int32 i = 0; i < Length; i++)
	{
		TSet<FString> BtnIDs;
		for (auto& Btn : QuestionLib[i].Buttons)
		{
			BtnIDs.Add(Btn.ButtonID);
		}
		if (!BtnIDs.Includes(QuestionLib[i].Answer.XhSet))
		{
			FString XhLog = FString::Printf(TEXT("InitData:'%s'的答案与选项不符！"), *QuestionLib[i].Question.Content.ToString());
			UXhTool::WriteLog(this, XhLog);
			Answers.Empty();
			return false;
		}
		else
		{
			Answers.Add(i, QuestionLib[i].Answer);
		}
	}
	return true && Length > 0;
}

// Called every frame
void AXhAnswerSystemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

