#include "Base/System/Answer/XhAnswerBase.h"
#include "Base/UMG/UI_XhAnswerBase.h"
#include "Components/WidgetComponent.h"

AXhAnswerBase::AXhAnswerBase()
{
	XhRoot = CreateDefaultSubobject<USceneComponent>(TEXT("XhRoot"));
	AnswerWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("AnswerWidget"));
	/*
	* UWidgetComponent::SetWidgetClass->UUserWidget::CreateWidget->UUserWidget::CreateWidgetInstance->UUserWidget::CreateInstanceInternal   NewWidget->Initialize();
	* UUserWidget::Initialize->UUserWidget::NativeOnInitialized->OnInitialized();	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category="User Interface")
	*/
	AnswerWidget->SetWidgetClass(UI_XhAnswer.Get());


	if (AnswerWidget)
	{
		UI_XhAnswerBase = Cast<UUI_XhAnswerBase>(AnswerWidget->GetUserWidgetObject());
	}
	//XhAnswerSystemBase = nullptr;
}

void AXhAnswerBase::XhInitialize_Implementation()
{
}

void AXhAnswerBase::XhConstruct()
{
	Super::XhConstruct();
	if (UI_XhAnswerBase)
	{
		UI_XhAnswerBase->XhTitleText = GameTitle;
		UI_XhAnswerBase->XhQuestionText = QuestionLib.Question;
		UI_XhAnswerBase->ButtonContents = QuestionLib.Buttons;
	}
}

void AXhAnswerBase::BeginPlay()
{
	XhInitialize();
	Super::BeginPlay();
}
