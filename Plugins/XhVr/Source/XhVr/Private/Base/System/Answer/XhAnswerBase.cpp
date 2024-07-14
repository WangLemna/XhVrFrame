#include "Base/System/Answer/XhAnswerBase.h"
#include "Base/UMG/UI_XhAnswerBase.h"
#include "Components/WidgetComponent.h"

AXhAnswerBase::AXhAnswerBase()
{
	XhRoot = CreateDefaultSubobject<USceneComponent>(TEXT("XhRoot"));
	AnswerWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("AnswerWidget"));
	RootComponent = XhRoot;
	AnswerWidget->SetupAttachment(XhRoot);
}

void AXhAnswerBase::XhRegisterComplete()
{
	if (UUI_XhAnswerBase* UI_XhAnswerBase = Cast<UUI_XhAnswerBase>(AnswerWidget->GetWidget()))
	{
		UI_XhAnswerBase->XhTitleText = GameTitle;
		UI_XhAnswerBase->XhQuestionText = QuestionLib.Question;
		UI_XhAnswerBase->ButtonContents = QuestionLib.Buttons;
	}
}

void AXhAnswerBase::BeginPlay()
{
	XH_BP_EXEC_B(XhBegin)
	Super::BeginPlay();
	XhRegisterComplete();
	XH_BP_EXEC_E(XhBegin)
}

void AXhAnswerBase::XhNativeClicked(const FString& ButtonID, UXhButton* Button, const FString& SubmitBtnID)
{
	if (ButtonID == SubmitBtnID)
	{
		XhAnswerSystemBase->Selects.Add(XhAnswerSystemBase->QuestionIndex - 1, SelectSet);
		if (bSpawnTip)
		{
			CreateTip();
		}
		else
		{
			CreateNextQuestion();
		}
	}
	else
	{
		switch (QuestionLib.QuestionType)
		{
		case EQuestionType::One:
		{
			if (UUI_XhAnswerBase* UI_XhAnswerBase = Cast<UUI_XhAnswerBase>(AnswerWidget->GetWidget()))
			{
				for (auto& Temp : UI_XhAnswerBase->ButtonChildren)
				{
					if (SelectSet.XhSet.Contains(Temp->ButtonID))
					{
						FButtonStyle ButtonStyle = Temp->GetStyle();
						ButtonStyle.SetNormal(ClickBefore);
						Temp->SetStyle(ButtonStyle);
						SelectSet.XhSet.Empty();
						break;
					}
				}
			}
		}
		break;
		case EQuestionType::Multi:
			break;
		default:
			break;
		}
		FButtonStyle ButtonStyle = Button->GetStyle();
		if (SelectSet.XhSet.Contains(ButtonID))
		{
			ButtonStyle.SetNormal(ClickBefore);
			SelectSet.XhSet.Remove(ButtonID);
		}
		else
		{
			ButtonStyle.SetNormal(ClickAfter);
			SelectSet.XhSet.Add(ButtonID);
		}
		Button->SetStyle(ButtonStyle);
	}
}

void AXhAnswerBase::CreateTip_Implementation()
{

}

void AXhAnswerBase::CreateNextQuestion_Implementation()
{
	XhAnswerSystemBase->NextQuestion();
	Destroy();
}

