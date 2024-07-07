// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#define XH_DELAY_MACRO_COMBINE_INTER(A,B,C) A##B##C
//#define XH_DELAY_MACRO_COMBINE(A,B,C) XH_DELAY_MACRO_COMBINE_INTER(A,B,C)
#define XH_DELAY_MACRO_COMBINE(A,B) A##B
#define TIMERHANDEL_VAR(A) XH_DELAY_MACRO_COMBINE(XhTH_,A)
#define AUTO_VAR(A) XH_DELAY_MACRO_COMBINE(XhAuto_,A)
#define XH_DELAY_B(Var) FTimerHandle TIMERHANDEL_VAR(Var);\
	auto AUTO_VAR(Var) = [&] {\
	if (TIMERHANDEL_VAR(Var).IsValid())\
	{\
		GetWorld()->GetTimerManager().ClearTimer(TIMERHANDEL_VAR(Var));\
	}

#define XH_DELAY_E(Var,DelayTime) };\
GetWorld()->GetTimerManager().SetTimer(TIMERHANDEL_VAR(Var), AUTO_VAR(Var), DelayTime, false);


#if 0
//UKismetSystemLibrary::Delay(GetWorld(), FadeInDuration, FLatentActionInfo());
FTimerHandle FadeInTimerHandle;
auto FadeIn = [&] {
	FTimerHandle FadeOutTimerHandle;
	auto FadeOut = [&] {
		if (FadeOutTimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(FadeOutTimerHandle);
		}
		XhClearWalk();
		bIsWalking = false;
		XhClearSpline();
		bStartWalk = false;
	};

	if (FadeInTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(FadeInTimerHandle);
	}
	XhWalker->SetActorLocationAndRotation(FinalWalkLocation, FinalWalkRotation);
	APlayerCameraManager* PCM = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	check(PCM);
	PCM->StartCameraFade(1.f, 0.f, FadeOutDuration, FadeColor, false, false);
	GetWorld()->GetTimerManager().SetTimer(FadeOutTimerHandle, FadeOut, FadeOutDuration, false);
};
GetWorld()->GetTimerManager().SetTimer(FadeInTimerHandle, FadeIn, FadeInDuration, false);
#endif

