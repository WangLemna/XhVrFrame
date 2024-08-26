// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AN_DestroyXhActor.h"
#include "Kismet/GameplayStatics.h"
#include "Base/GameBase/XhCharacter.h"
#include "Base/GameBase/XhPlayerState.h"

void UAN_DestroyXhActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}
void UAN_DestroyXhActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	AXhCharacter* XhPlayer = Cast<AXhCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	AXhPlayerState* XhPlayerState = Cast<AXhPlayerState>(XhPlayer->GetPlayerState());
	FString XhClassName = MyActor->GetClass()->GetName().LeftChop(2);
	TArray<AXhActorBase*> DestroyActors = XhPlayerState->GetXhActors(Id, XhClassName, TagName);
	for (AXhActorBase* Temp : DestroyActors)
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

