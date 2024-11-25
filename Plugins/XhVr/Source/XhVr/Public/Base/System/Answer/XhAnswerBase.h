// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/XhWidgetActor.h"
#include "Base/System/XhAnswerSystemBase.h"
#include "XhAnswerBase.generated.h"

class UWidgetComponent;
class UUI_XhAnswerBase;
UCLASS()
class XHVR_API AXhAnswerBase : public AXhWidgetActor
{
	GENERATED_BODY()

public:

	UPROPERTY(Category = "XhAnswerBase", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> XhRoot;
	UPROPERTY(Category = "XhAnswerBase", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> AnswerWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XhVar|BlueprintGet", meta = (ExposeOnSpawn = "true"))
	FQuesionLib QuestionLib;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XhVar|BlueprintGet", meta = (ExposeOnSpawn = "true"))
	AXhAnswerSystemBase* XhAnswerSystemBase;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|BlueprintGet")
	//UUI_XhAnswerBase* UI_XhAnswerBase;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Settings")
	FTextContent GameTitle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Settings")
	FSlateBrush ClickBefore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Settings")
	FSlateBrush ClickAfter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Settings|Tip")
	bool bSpawnTip;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Settings|Tip")
	TSubclassOf<AActor> TipClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Settings|Tip")
	FTransform TipTransform;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|Settings|Tip")
	//float TipDuringTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XhVar|BlueprintChange")
	FXhSet SelectSet;
public:
	// Sets default values for this actor's properties
	AXhAnswerBase();
	void XhRegisterComplete();
	UFUNCTION(BlueprintCallable)//BlueprintNativeEvent
	void XhNativeClicked(const FString& ButtonID, UXhButton* Button, const FString& SubmitBtnID);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CreateTip();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CreateNextQuestion();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};

