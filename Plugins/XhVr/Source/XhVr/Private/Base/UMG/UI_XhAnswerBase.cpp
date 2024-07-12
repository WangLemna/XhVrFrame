#include "Base/UMG/UI_XhAnswerBase.h"
#include "Components/TextBlock.h"
#include "UI/XhButton.h"
#include "Components/ButtonSlot.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

void UUI_XhAnswerBase::XhNativeConstruct()
{
	Super::XhNativeConstruct();
}

void UUI_XhAnswerBase::XhConstruct_Implementation()
{

}

void UUI_XhAnswerBase::XhNativeOnInitialized()
{
	Super::XhNativeOnInitialized();

	TitleText->SetText(XhTitleText.Content);

	FSlateFontInfo TitleFont = TitleText->GetFont();
	TitleFont.Size = XhTitleText.FontSize;
	TitleText->SetFont(TitleFont);

	QuestionText->SetText(XhQuestionText.Content);

	FSlateFontInfo QuestionFont = QuestionText->GetFont();
	QuestionFont.Size = XhQuestionText.FontSize;
	QuestionText->SetFont(QuestionFont);
}

void UUI_XhAnswerBase::XhInitialized_Implementation()
{
	if (UVerticalBox* ButtonVerticalContainer = Cast<UVerticalBox>(ButtonContainer))
	{
		if (BtnWidget)
		{
			//生成选项
			for (auto& Temp : ButtonContents)
			{
				UUserWidget* XhButton = CreateWidget<UXhUserWidget>(GetWorld(), BtnWidget);

				UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(ButtonVerticalContainer->AddChild(XhButton));
				VerticalBoxSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
				VerticalBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
			}
		}
		if (SubmitBtnWidget)
		{
			//生成提交按钮
			UUserWidget* SubmitBtn = CreateWidget<UXhUserWidget>(GetWorld(), SubmitBtnWidget);

			UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(ButtonVerticalContainer->AddChild(SubmitBtn));
			VerticalBoxSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
			VerticalBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
		}
	}
}

void UUI_XhAnswerBase::NativeOnInitialized()
{
	XhNativeOnInitialized();
	Super::NativeOnInitialized();
	XhInitialized();
}

void UUI_XhAnswerBase::NativeConstruct()
{
	Super::NativeConstruct();
	XhNativeConstruct();
	XhConstruct();
}

void UUI_XhAnswerBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
