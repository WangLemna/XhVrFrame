// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XhUserWidget.h"
#include "Components/PanelWidget.h"
#include "UI/XhButton.h"
#include "UI/XhWidgetActor.h"

void UXhUserWidget::NativeInit()
{
	UPanelWidget* RootPanel = Cast<UPanelWidget>(GetRootWidget());
	//ButtonChildren.Empty();
	GetAllXhButton(RootPanel, ButtonChildren);
	for (UXhButton* XhButton : ButtonChildren)
	{
		XhButtonInit(XhButton);
	}
}

void UXhUserWidget::XhButtonInit(UXhButton* XhButton)
{
	if (XhButton->bIsAutoBind)
	{
		XhButton->OnXhClicked.AddDynamic(XhWidgetActor, &AXhWidgetActor::XhClicked);
		XhButton->OnXhClicked.AddDynamic(this, &UXhUserWidget::XhUpdateClickTime);
		XhButton->OnXhUnhovered.AddDynamic(XhWidgetActor, &AXhWidgetActor::XhUnHovered);
		XhButton->OnXhHovered.AddDynamic(XhWidgetActor, &AXhWidgetActor::XhHovered);
		XhButton->OnXhPressed.AddDynamic(XhWidgetActor, &AXhWidgetActor::XhPressed);
		XhButton->OnXhReleased.AddDynamic(XhWidgetActor, &AXhWidgetActor::XhReleased);
	}
	XhButton->LastClickTime = XhButton->DuringTime;
	XhButton->bIsUpdateTime = false;
}

void UXhUserWidget::XhUpdateClickTime(const FString& ButtonID, UXhButton* Button)
{
	switch (Button->DuringMode)
	{
	case EDuringMode::DisableButton:
		Button->SetIsEnabled(false);
		break;
	case EDuringMode::DisableClickEvent:
		Button->bIsUpdateTime = true;
		break;
	default:
		break;
	}
	Button->LastClickTime = 0;
	ButtonNeedUpdateChildren.Add(Button);
}

void UXhUserWidget::AddDynamicXhButton(const TArray<UXhButton*> DynamicButtons)
{
	for (UXhButton* XhButton : DynamicButtons)
	{
		XhButtonInit(XhButton);
	}
}

void UXhUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UXhUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	int Num = ButtonNeedUpdateChildren.Num();
	for (int32 i = Num - 1; i >= 0; i--)
	{
		if (ButtonNeedUpdateChildren[i] != nullptr)
		{
			if (ButtonNeedUpdateChildren[i]->LastClickTime >= ButtonNeedUpdateChildren[i]->DuringTime)
			{
				switch (ButtonNeedUpdateChildren[i]->DuringMode)
				{
				case EDuringMode::DisableButton:
					ButtonNeedUpdateChildren[i]->SetIsEnabled(true);
					break;
				case EDuringMode::DisableClickEvent:
					ButtonNeedUpdateChildren[i]->bIsUpdateTime = false;
					break;
				default:
					break;
				}
				ButtonNeedUpdateChildren.RemoveAt(i);
				continue;
			}
			else
			{
				ButtonNeedUpdateChildren[i]->LastClickTime += InDeltaTime;
			}
		}
		else
		{
			ButtonNeedUpdateChildren.RemoveAt(i);
		}
	}
}

void UXhUserWidget::GetAllXhButton(UPanelWidget* RootPanel, TArray<UXhButton*>& XhButtonArray)
{
	XhButtonArray.Empty();
	if (!RootPanel)
	{
		return;
	}
	TArray<UWidget*> Children = RootPanel->GetAllChildren();
	for (auto Temp : Children)
	{
		if (UXhUserWidget* MySon = Cast<UXhUserWidget>(Temp))
		{
			MySon->XhWidgetActor = XhWidgetActor;
			MySon->NativeInit();
			continue;
		}
		if (UPanelWidget* MySon = Cast<UPanelWidget>(Temp))
		{
			if (MySon->GetChildrenCount())
			{
				GetAllXhButton(MySon, XhButtonArray);
			}
			if (UXhButton* MyButton = Cast<UXhButton>(MySon))
			{
				XhButtonArray.AddUnique(MyButton);
			}
		}
	}
}

