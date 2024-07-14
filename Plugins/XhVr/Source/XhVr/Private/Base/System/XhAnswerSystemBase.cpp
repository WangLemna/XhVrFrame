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
	XhBegin();
}

void AXhAnswerSystemBase::NextQuestion_Implementation()
{
	if (QuestionLibs.IsValidIndex(QuestionIndex))
	{
		if (AnswerActor)
		{
			FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
			SpawnParameters.CustomPreSpawnInitalization = 
				[&](AActor* InActor)
				{
					AXhAnswerBase* XhAnswerBase = Cast<AXhAnswerBase>(InActor);
					XhAnswerBase->QuestionLib = QuestionLibs[QuestionIndex];
					XhAnswerBase->XhAnswerSystemBase = this;
				};
			GetWorld()->SpawnActor<AXhAnswerBase>(AnswerActor, AnswerActorTransform, SpawnParameters);
			QuestionIndex++;
		}
		else
		{
			UXhTool::WriteLog(this, TEXT("NextQuestion:AnswerActor无效"));
		}
	}
	else
	{
		XhAnswerFinish();
	}
}

bool AXhAnswerSystemBase::InitData()
{
	int32 Length = QuestionLibs.Num();
	for (int32 i = 0; i < Length; i++)
	{
		if (QuestionLibs[i].Answer.XhSet.IsEmpty())
		{
			FString XhLog = FString::Printf(TEXT("InitData:'%s'答案为空！"), *QuestionLibs[i].Question.Content.ToString());
			UXhTool::WriteLog(this, XhLog);
			Answers.Empty();
			return false;
		}
		if (QuestionLibs[i].QuestionType == EQuestionType::One && QuestionLibs[i].Answer.XhSet.Num() != 1)
		{
			FString XhLog = FString::Printf(TEXT("InitData:'%s'答案的与问题类型不符！"), *QuestionLibs[i].Question.Content.ToString());
			UXhTool::WriteLog(this, XhLog);
			Answers.Empty();
			return false;
		}
		TSet<FString> BtnIDs;
		for (auto& Btn : QuestionLibs[i].Buttons)
		{
			BtnIDs.Add(Btn.ButtonID);
		}
		if (!BtnIDs.Includes(QuestionLibs[i].Answer.XhSet))
		{
			FString XhLog = FString::Printf(TEXT("InitData:'%s'的答案与选项不符！"), *QuestionLibs[i].Question.Content.ToString());
			UXhTool::WriteLog(this, XhLog);
			Answers.Empty();
			return false;
		}
		else
		{
			Answers.Add(i, QuestionLibs[i].Answer);
		}
	}
	return true && Length > 0;
}

TArray<int32> AXhAnswerSystemBase::GetErrorQuestionsIndex()
{
	TArray<int32> ErrorQuestionsIndex;
	for (auto& Temp : Answers)
	{
		if (Selects.Contains(Temp.Key))
		{
			if (Temp.Value.XhSet.CreateConstIterator() == Selects.Find(Temp.Key)->XhSet.CreateConstIterator())
			{
				continue;
			}
		}
		ErrorQuestionsIndex.Add(Temp.Key);
	}
	return ErrorQuestionsIndex;
}

int32 AXhAnswerSystemBase::GetErrorQuestionsCount()
{
	int32 Count = 0;
	for (auto& Temp : Answers)
	{
		if (Selects.Contains(Temp.Key))
		{
			if (Temp.Value.XhSet.CreateConstIterator() == Selects.Find(Temp.Key)->XhSet.CreateConstIterator())
			{
				continue;
			}
		}
		Count++;
	}
	return Count;
}

TArray<FText> AXhAnswerSystemBase::GetErrorQuestions()
{
	TArray<FText> ErrorQuestions;
	for (auto& Temp : Answers)
	{
		if (Selects.Contains(Temp.Key))
		{
			if (Temp.Value.XhSet.CreateConstIterator() == Selects.Find(Temp.Key)->XhSet.CreateConstIterator())
			{
				continue;
			}
		}
		ErrorQuestions.Add(QuestionLibs[Temp.Key].Question.Content);
	}
	return ErrorQuestions;
}

// Called every frame
void AXhAnswerSystemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

