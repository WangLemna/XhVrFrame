// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Type/XhCore.h"
#include "IXhOculusEvent.generated.h"

// This class does not need to be modified.
//UINTERFACE(MinimalAPI)
UINTERFACE(BlueprintType, Blueprintable, MinimalAPI)
class UXhOculusEvent : public UInterface
{
	GENERATED_BODY()
	//GENERATED_UINTERFACE_BODY()
};

/**
 * 与FOculusEventMode,AXhOperateActorBase有关联
 */
//UINTERFACE(BlueprintType, Blueprintable, MinimalAPI)
class XHVR_API IXhOculusEvent : public IInterface
{
	//GENERATED_BODY()
	GENERATED_IINTERFACE_BODY()
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//A
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "XhOculusEvent")
	void OculusA(EButtonEvent InButtonEvent);
	//B
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "XhOculusEvent")
	void OculusB(EButtonEvent InButtonEvent);
	//X
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "XhOculusEvent")
	void OculusX(EButtonEvent InButtonEvent);
	//Y
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "XhOculusEvent")
	void OculusY(EButtonEvent InButtonEvent);
	//左摇杆
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "XhOculusEvent")
	void OculusJoystickL(EButtonEvent InButtonEvent);
	//右摇杆
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "XhOculusEvent")
	void OculusJoystickR(EButtonEvent InButtonEvent);
	//左手握
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "XhOculusEvent")
	void OculusGripL(EButtonEvent InButtonEvent);
	//右手握
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "XhOculusEvent")
	void OculusGripR(EButtonEvent InButtonEvent);
	//左扳机
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "XhOculusEvent")//BlueprintImplementableEvent
	void OculusTriggerL(EButtonEvent InButtonEvent);
	//右扳机
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "XhOculusEvent")
	void OculusTriggerR(EButtonEvent InButtonEvent);
};
