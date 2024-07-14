// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/XhUserWidget.h"
#include "UI_XhButton.generated.h"

class UTextBlock;
class UXhButton;

/**
 * 
 */
UCLASS()
class XHVR_API UUI_XhButton : public UXhUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UXhButton* Button;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UTextBlock* ButtonText;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
