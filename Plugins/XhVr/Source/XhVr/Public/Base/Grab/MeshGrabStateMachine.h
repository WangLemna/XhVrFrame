// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Type/XhCore.h"
#include "MeshGrabStateMachine.generated.h"

/**
 * 
 */
UCLASS()
class XHVR_API UMeshGrabStateMachine : public UObject
{
	GENERATED_BODY()
public:
	EXhGrabState CurrentGrabState;
	EXhGrabState LastGrabState;
};
