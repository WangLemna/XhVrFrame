// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ContentWidget.h"

#include "UObject/ObjectMacros.h"
#include "Input/Reply.h"
#include "Styling/SlateTypes.h"
#include "Widgets/SWidget.h"

#include "Type/XhType.h"
#include "XhButton.generated.h"

class SButton;
class USlateWidgetStyleAsset;


/**
 * The button is a click-able primitive widget to enable basic interaction, you
 * can place any other widget inside a button to make a more complex and
 * interesting click-able element in your UI.
 *
 * * Single Child
 * * Clickable
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnXhButtonClickedEvent, const FString&, ButtonID, UXhButton*, XhButton);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnXhButtonPressedEvent, const FString&, ButtonID, UXhButton*, XhButton);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnXhButtonReleasedEvent, const FString&, ButtonID, UXhButton*, XhButton);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnXhButtonHoverEvent, const FString&, ButtonID, UXhButton*, XhButton);
UCLASS()
class XHVR_API UXhButton : public UContentWidget
{
	GENERATED_UCLASS_BODY()
	
public:
	UE_DEPRECATED(5.2, "Direct access to WidgetStyle is deprecated. Please use the getter and setter.")
	/** The button style used at runtime */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "GetStyle", Setter = "SetStyle", BlueprintSetter = "SetStyle", Category = "Appearance", meta = (DisplayName = "Style"))
	FButtonStyle WidgetStyle;

	UE_DEPRECATED(5.2, "Direct access to ColorAndOpacity is deprecated. Please use the getter and setter.")
	/** The color multiplier for the button content */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetColorAndOpacity", Category = "Appearance", meta = (sRGB = "true"))
	FLinearColor ColorAndOpacity;

	UE_DEPRECATED(5.2, "Direct access to BackgroundColor is deprecated. Please use the getter and setter.")
	/** The color multiplier for the button background */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetBackgroundColor", Category = "Appearance", meta = (sRGB = "true"))
	FLinearColor BackgroundColor;

	UE_DEPRECATED(5.2, "Direct access to ClickMethod is deprecated. Please use the getter and setter.")
	/** The type of mouse action required by the user to trigger the buttons 'Click' */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetClickMethod", Category = "Interaction", AdvancedDisplay)
	TEnumAsByte<EButtonClickMethod::Type> ClickMethod;

	UE_DEPRECATED(5.2, "Direct access to TouchMethod is deprecated. Please use the getter and setter.")
	/** The type of touch action required by the user to trigger the buttons 'Click' */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetTouchMethod", Category = "Interaction", AdvancedDisplay)
	TEnumAsByte<EButtonTouchMethod::Type> TouchMethod;

	UE_DEPRECATED(5.2, "Direct access to PressMethod is deprecated. Please use the getter and setter.")
	/** The type of keyboard/gamepad button press action required by the user to trigger the buttons 'Click' */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetPressMethod", Category = "Interaction", AdvancedDisplay)
	TEnumAsByte<EButtonPressMethod::Type> PressMethod;

	UE_DEPRECATED(5.2, "Direct access to IsFocusable is deprecated. Please use the getter.")
	/** Sometimes a button should only be mouse-clickable and never keyboard focusable. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter, Category = "Interaction")
	bool IsFocusable;

public:
	/** 唯一标识符 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Xh")
	FString ButtonID;

	/** 是否自动绑定 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Xh")
	bool bIsAutoBind;

	/** 点击的间隔时间 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Xh")
	float DuringTime;

	/** 设置间隔模式 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Xh")
	EDuringMode DuringMode;

public:
	/** Called when the button is clicked */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnXhButtonClickedEvent OnXhClicked;

	/** Called when the button is pressed */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnXhButtonPressedEvent OnXhPressed;

	/** Called when the button is released */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnXhButtonReleasedEvent OnXhReleased;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnXhButtonHoverEvent OnXhHovered;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnXhButtonHoverEvent OnXhUnhovered;

public:
	/** Sets the color multiplier for the button background */
	UFUNCTION(BlueprintCallable, Category = "Button|Appearance")
	void SetStyle(const FButtonStyle& InStyle);

	const FButtonStyle& GetStyle() const;

	/** Sets the color multiplier for the button content */
	UFUNCTION(BlueprintCallable, Category = "Button|Appearance")
	void SetColorAndOpacity(FLinearColor InColorAndOpacity);

	FLinearColor GetColorAndOpacity() const;

	/** Sets the color multiplier for the button background */
	UFUNCTION(BlueprintCallable, Category = "Button|Appearance")
	void SetBackgroundColor(FLinearColor InBackgroundColor);

	FLinearColor GetBackgroundColor() const;

	/**
	 * Returns true if the user is actively pressing the button.  Do not use this for detecting 'Clicks', use the OnClicked event instead.
	 *
	 * @return true if the user is actively pressing the button otherwise false.
	 */
	UFUNCTION(BlueprintCallable, Category = "Button")
	bool IsPressed() const;

	UFUNCTION(BlueprintCallable, Category = "Button")
	void SetClickMethod(EButtonClickMethod::Type InClickMethod);

	EButtonClickMethod::Type GetClickMethod() const;

	UFUNCTION(BlueprintCallable, Category = "Button")
	void SetTouchMethod(EButtonTouchMethod::Type InTouchMethod);

	EButtonTouchMethod::Type GetTouchMethod() const;

	UFUNCTION(BlueprintCallable, Category = "Button")
	void SetPressMethod(EButtonPressMethod::Type InPressMethod);

	EButtonPressMethod::Type GetPressMethod() const;

	bool GetIsFocusable() const;

	/**
	 * Adds a new child widget to the container.  Returns the base slot type,
	 * requires casting to turn it into the type specific to the container.
	 */
	/*UFUNCTION(BlueprintCallable, Category = "Widget|Panel")
	UPanelSlot* AddChild(UWidget* Content);*/
public:

	//~ Begin UWidget Interface
	virtual void SynchronizeProperties() override;
	//~ End UWidget Interface

	//~ Begin UVisual Interface
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	//~ End UVisual Interface

	//~ Begin UObject Interface
	virtual void PostLoad() override;
	//~ End UObject Interface

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif


protected:

	// UPanelWidget
	virtual UClass* GetSlotClass() const override;
	virtual void OnSlotAdded(UPanelSlot* Slot) override;
	virtual void OnSlotRemoved(UPanelSlot* Slot) override;
	// End UPanelWidget

protected:
	/** Handle the actual click event from slate and forward it on */
	FReply SlateHandleClicked();
	void SlateHandlePressed();
	void SlateHandleReleased();
	void SlateHandleHovered();
	void SlateHandleUnhovered();

	// Initialize IsFocusable in the constructor before the SWidget is constructed.
	void InitIsFocusable(bool InIsFocusable);
protected:
	//~ Begin UWidget Interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
#if WITH_EDITOR
	virtual TSharedRef<SWidget> RebuildDesignWidget(TSharedRef<SWidget> Content) override { return Content; }
#endif
	//~ End UWidget Interface

#if WITH_ACCESSIBILITY
	virtual TSharedPtr<SWidget> GetAccessibleWidget() const override;
#endif
public:
	float LastClickTime;
	bool bIsUpdateTime;
protected:
	/** Cached pointer to the underlying slate button owned by this UWidget */
	TSharedPtr<SButton> MyButton;
};

