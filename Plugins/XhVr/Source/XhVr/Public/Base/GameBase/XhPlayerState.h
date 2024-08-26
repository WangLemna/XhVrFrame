// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Type/XhCore.h"
#include "XhPlayerState.generated.h"

class AXhActorBase;
/**
 * 
 */
UCLASS()
class XHVR_API AXhPlayerState : public APlayerState
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XhVar|Base")
	TMap<FString, FXhActorBaseArray> XhActorsData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XhVar|Base")
	TMap<FString, AXhActorBase*> XhActorsDataById;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XhVar|Base")
	TArray<AXhActorBase*> XhOperaActors;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<AXhActorBase*> GetXhActorsByClassName(const FString& InClassName);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	AXhActorBase* GetXhActorById(const FString& InId);

public:
	TArray<AXhActorBase*> GetXhActors(const FString& InId, const FString& InClassName, FName InTagName);
};
