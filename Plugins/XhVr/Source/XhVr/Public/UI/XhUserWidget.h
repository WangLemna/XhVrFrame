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
	void XhNativeConstruct();

	void NativeInit();

	void XhButtonInit(UXhButton* XhButton);
public:
	int32 XhConstructOrder;
	TArray<UXhButton*> ButtonChildren;
public:
	/** XhUserWidget */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Xh")
	AXhWidgetActor* XhWidgetActor;

	UFUNCTION(BlueprintImplementableEvent)
	void XhConstruct();
	UFUNCTION()
	void XhUpdateClickTime(const FString& ButtonID, UXhButton* Button);//UPARAM(ref) 
	UFUNCTION(BlueprintCallable, meta = (Keywords = "AddDynamicXhButton", DisplayName = "AddDynamicXhButton"))
	void AddDynamicXhButton(const TArray<UXhButton*> DynamicButtons);
protected:
	TArray<UXhButton*> ButtonNeedUpdateChildren;

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void GetAllXhButton(UPanelWidget* RootPanel, TArray<UXhButton*>& XhButtonArray);
};



