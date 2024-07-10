﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/XhUserWidget.h"
#include "UI_XhAnswerBase.generated.h"

class UTextBlock;

/**
 *
 */
UCLASS()
class XHVR_API UUI_XhAnswerBase : public UXhUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ControlObj;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
