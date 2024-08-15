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
 * 
 */
//UINTERFACE(BlueprintType, Blueprintable, MinimalAPI)
class XHVR_API IXhOculusEvent : public IInterface
{
	//GENERATED_BODY()
	GENERATED_IINTERFACE_BODY()
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//A
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "XhOculusEvent")
	void OculusA(EButtonEvent InButtonEvent);
	//B
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "XhOculusEvent")
	void OculusB(EButtonEvent InButtonEvent);
	////左摇杆
	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "XhOculusEvent")
	//void OculusJoystickL(EButtonEvent InButtonEvent);
	////右摇杆
	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "XhOculusEvent")
	//void OculusJoystickR(EButtonEvent InButtonEvent);
	//左扳机
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "XhOculusEvent")
	void OculusTriggerL(EButtonEvent InButtonEvent);
	//右扳机
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "XhOculusEvent")
	void OculusTriggerR(EButtonEvent InButtonEvent);
	//X
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "XhOculusEvent")
	void OculusX(EButtonEvent InButtonEvent);
	//Y
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "XhOculusEvent")
	void OculusY(EButtonEvent InButtonEvent);
};
