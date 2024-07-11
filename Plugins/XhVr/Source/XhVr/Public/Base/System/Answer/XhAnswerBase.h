// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/XhWidgetActor.h"
#include "Type/XhCore.h"
#include "Base/System/XhAnswerSystemBase.h"
#include "XhAnswerBase.generated.h"
UCLASS()
class XHVR_API AXhAnswerBase : public AXhWidgetActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|BlueprintChange", meta = (ExposeOnSpawn = "true"))
	FQuesionLib QuestionLib;

public:
	// Sets default values for this actor's properties
	AXhAnswerBase();
	//AXhAnswerBase(FQuesionLib QuestionLib);

};

