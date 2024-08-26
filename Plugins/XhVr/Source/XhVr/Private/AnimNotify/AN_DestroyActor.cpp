// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AN_DestroyActor.h"

#include "Kismet/GameplayStatics.h"

void UAN_DestroyActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}
void UAN_DestroyActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
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
		if (DelayTime < 0.1f)
		{
			Temp->Destroy();
		}
		else
		{
			Temp->SetLifeSpan(DelayTime);
		}
	}
}

