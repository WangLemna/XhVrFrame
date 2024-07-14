// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define XH_MACRO_COMBINE2(A, B) A##B
#define XH_MACRO_COMBINE3(A, B, C) A##B##C
#define XH_MACRO_COMBINE4(A, B, C, D) A##B##C##D
#define TIMERHANDEL_VAR(A) XH_MACRO_COMBINE2(XhTH_,A)
#define AUTO_VAR(A) XH_MACRO_COMBINE2(XhAuto_,A)
#define XH_DELAY_B(Var) FTimerHandle TIMERHANDEL_VAR(Var);\
	auto AUTO_VAR(Var) = [&] {\
	if (TIMERHANDEL_VAR(Var).IsValid())\
	{\
		GetWorld()->GetTimerManager().ClearTimer(TIMERHANDEL_VAR(Var));\
	}

#define XH_DELAY_E(Var,DelayTime) };\
GetWorld()->GetTimerManager().SetTimer(TIMERHANDEL_VAR(Var), AUTO_VAR(Var), DelayTime, false);

#define XH_BP_EXEC_VAR(A) XH_MACRO_COMBINE2(A, Order)
#define XH_BP_EXEC_B(FuncName) XH_BP_EXEC_VAR(FuncName)++;

#define XH_BP_EXEC_E(FuncName) if (XH_BP_EXEC_VAR(FuncName) > 0)\
	{\
		XH_BP_EXEC_VAR(FuncName)--;\
	}\
	else\
	{\
		FuncName();\
	}

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

