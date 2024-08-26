// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AN_SetHiddenActor.h"
#include "Kismet/GameplayStatics.h"

void UAN_SetHiddenActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}
void UAN_SetHiddenActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	TArray<AActor*> OutActors;
	if (TagName == NAME_None || TagName == FName(TEXT("")))
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), MyActor, OutActors);
	}
	else
	{
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), MyActor, TagName, OutActors);
	}
	for (AActor* Temp : OutActors)
	{
		Temp->SetActorHiddenInGame(bHidden);
	}
}

