// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/XhUserWidget.h"
#include "Type/XhCore.h"
#include "UI_XhAnswerBase.generated.h"

class UTextBlock;
class UPanelWidget;
class UXhButton;
class UUserWidget;

/**
 *
 */
UCLASS()
class XHVR_API UUI_XhAnswerBase : public UXhUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TitleText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestionText;
	UPROPERTY(meta = (BindWidget))
	UPanelWidget* ButtonContainer;

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XhVar|BlueprintGet")
	FTextContent XhTitleText;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XhVar|BlueprintGet")
	FTextContent XhQuestionText;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XhVar|BlueprintGet")
	TArray<FButtonContent> ButtonContents;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "XhVar|Settings")
	TSubclassOf<UUserWidget> SubmitBtnWidget;
	//选项按钮，C++写太麻烦
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "XhVar|Settings")
	TSubclassOf<UUserWidget> BtnWidget;
public:
	void XhNativeConstruct();
	UFUNCTION(BlueprintNativeEvent)
	void XhConstruct();

	void XhNativeOnInitialized();
	UFUNCTION(BlueprintNativeEvent)
	void XhInitialized();
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


};
