// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XhUserWidget.generated.h"

class AXhWidgetActor;
class UXhButton;
/**
 * 
 */
UCLASS()
class XHVR_API UXhUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** XhUserWidget */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Xh")
	AXhWidgetActor* XhWidgetActor;

	void NativeInit();

	void XhButtonInit(UXhButton* XhButton);

	UFUNCTION()
	void XhUpdateClickTime(const FString& ButtonID, UXhButton* Button);//UPARAM(ref) 
	UFUNCTION(BlueprintCallable, meta = (Keywords = "AddDynamicXhButton", DisplayName = "AddDynamicXhButton"))
	void AddDynamicXhButton(const TArray<UXhButton*> DynamicButtons);
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	TArray<UXhButton*> ButtonChildren;
	TArray<UXhButton*> ButtonNeedUpdateChildren;
	void GetAllXhButton(UPanelWidget* RootPanel, TArray<UXhButton*>& XhButtonArray);
};



