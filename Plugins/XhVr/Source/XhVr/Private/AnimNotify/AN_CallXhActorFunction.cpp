// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AN_CallXhActorFunction.h"
#include "Kismet/GameplayStatics.h"
#include "Base/GameBase/XhCharacter.h"
#include "Base/GameBase/XhPlayerState.h"

void UAN_CallXhActorFunction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}
void UAN_CallXhActorFunction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(MeshComp->GetWorld(), 0))
	{
		if (AXhCharacter* XhPlayer = Cast<AXhCharacter>(PC->K2_GetPawn()))
		{
			if (AXhPlayerState* XhPlayerState = Cast<AXhPlayerState>(XhPlayer->GetPlayerState()))
			{
				FString XhClassName = MyActor->GetClass()->GetName().LeftChop(2);
				TArray<AXhActorBase*> FunctionActors = XhPlayerState->GetXhActors(Id, XhClassName, TagName);
				for (AXhActorBase* Temp : FunctionActors)
				{
					UKismetSystemLibrary::K2_SetTimerForNextTick(Temp, FunctionName);
				}
			}
		}
	}
}
