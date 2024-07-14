#include "Base/UMG/UI_XhAnswerBase.h"
#include "Components/TextBlock.h"
#include "UI/XhButton.h"
#include "Components/ButtonSlot.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Base/UMG/UI_XhButton.h"

void UUI_XhAnswerBase::XhNativeConstruct()
{
	Super::XhNativeConstruct();

	TitleText->SetText(XhTitleText.Content);

	FSlateFontInfo TitleFont = TitleText->GetFont();
	TitleFont.Size = XhTitleText.FontSize;
	TitleText->SetFont(TitleFont);

	QuestionText->SetText(XhQuestionText.Content);

	FSlateFontInfo QuestionFont = QuestionText->GetFont();
	QuestionFont.Size = XhQuestionText.FontSize;
	QuestionText->SetFont(QuestionFont);
}

void UUI_XhAnswerBase::XhConstructComplete_Implementation()
{
	if (UVerticalBox* ButtonVerticalContainer = Cast<UVerticalBox>(ButtonContainer))
	{
		TArray<UXhButton*> DynamicButtons;
		if (BtnWidget)
		{
			//生成选项
			for (auto& Temp : ButtonContents)
			{
				UXhUserWidget* SelectButton = CreateWidget<UXhUserWidget>(GetWorld(), BtnWidget);
				if (UUI_XhButton* XhButton = Cast<UUI_XhButton>(SelectButton))
				{
					XhButton->ButtonText->SetText(Temp.ButtonText.Content);
					FSlateFontInfo XhButtonFont = XhButton->ButtonText->GetFont();
					XhButtonFont.Size = Temp.ButtonText.FontSize;
					TitleText->SetFont(XhButtonFont);
					XhButton->Button->ButtonID = Temp.ButtonID;
					DynamicButtons.Add(XhButton->Button);

					UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(ButtonVerticalContainer->AddChild(SelectButton));
					VerticalBoxSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
					VerticalBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
				}
			}
		}
		if (SubmitBtnWidget)
		{
			//生成提交按钮
			UXhUserWidget* SubmitBtn = CreateWidget<UXhUserWidget>(GetWorld(), SubmitBtnWidget);
			if (UUI_XhButton* XhButton = Cast<UUI_XhButton>(SubmitBtn))
			{
				DynamicButtons.Add(XhButton->Button);
			}

			UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(ButtonVerticalContainer->AddChild(SubmitBtn));
			VerticalBoxSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
			VerticalBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
		}
		AddDynamicXhButton(DynamicButtons);
	}
}

void UUI_XhAnswerBase::NativeConstruct()
{
	XhNativeConstruct();
	XH_BP_EXEC_B(XhConstruct)
	Super::NativeConstruct();
	XH_BP_EXEC_E(XhConstruct)
	XhConstructComplete();
}

void UUI_XhAnswerBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
