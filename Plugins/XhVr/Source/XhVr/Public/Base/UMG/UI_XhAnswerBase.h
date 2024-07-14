// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/XhUserWidget.h"
#include "Type/XhCore.h"
#include "UI_XhAnswerBase.generated.h"

class UTextBlock;
class UPanelWidget;
//class UXhButton;
class UUserWidget;

/**
 *
 */
UCLASS()
class XHVR_API UUI_XhAnswerBase : public UXhUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UTextBlock* TitleText;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UTextBlock* QuestionText;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UPanelWidget* ButtonContainer;

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XhVar|BlueprintGet")
	FTextContent XhTitleText;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XhVar|BlueprintGet")
	FTextContent XhQuestionText;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XhVar|BlueprintGet")
	TArray<FButtonContent> ButtonContents;
	//提交按钮，C++写太麻烦
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "XhVar|Settings")
	TSubclassOf<UUserWidget> SubmitBtnWidget;
	//选项按钮，C++写太麻烦
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "XhVar|Settings")
	TSubclassOf<UUserWidget> BtnWidget;
public:
	void XhNativeConstruct();
	UFUNCTION(BlueprintNativeEvent)
	void XhConstructComplete();
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


};
