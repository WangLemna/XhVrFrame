// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/GameBase/XhGameMode.h"
#include "Base/GameBase/XhGameState.h"
#include "Base/GameBase/XhPlayerController.h"
#include "Base/GameBase/XhPlayerState.h"
#include "Base/GameBase/XhCharacter.h"
#include "Kismet/GameplayStatics.h"

AXhGameMode::AXhGameMode()
{
	GameStateClass = AXhGameState::StaticClass();
	PlayerControllerClass = AXhPlayerController::StaticClass();
	PlayerStateClass = AXhPlayerState::StaticClass();
	DefaultPawnClass = AXhCharacter::StaticClass();
	XhVrSettings = GetMutableDefault<UXhVrSettings>();
	XhBeginOrder = -1;
}

void AXhGameMode::InitLog()
{
	//FString XhLogPath = FPaths::ProjectDir() + "Xh/";
	FString XhLogPath = XhVrSettings->LogPath;
	//FString LogFileName = FApp::GetProjectName();
	FString LogFileName = XhVrSettings->LogFileName;
	if (FPaths::DirectoryExists(XhLogPath))
	{
		TArray<FString> FilePathList;
		IFileManager::Get().FindFilesRecursive(FilePathList, *XhLogPath, TEXT("*"), true, true);
		int64 LogSize = -1;
		for (auto& Temp : FilePathList)
		{
			LogSize += IFileManager::Get().GetStatData(*Temp).FileSize;
		}
		if (XhVrSettings->MaxLogSize <= LogSize)//XhMaxLogSize
		{
			if (IFileManager::Get().DeleteDirectory(*XhLogPath, true, true))
			{
				UE_LOG(XhCharacterLog, Warning, TEXT("'%s' ռ�ÿռ������ɾ��"), *XhLogPath);
			}
			else
			{
				UE_LOG(XhCharacterLog, Error, TEXT("'%s' ɾ��ʧ�ܣ����ֶ�ɾ����"), *XhLogPath);
			}
		}
		else
		{
			if (FPaths::FileExists(XhLogPath + LogFileName + ".log"))
			{
				if (FPaths::FileExists(XhLogPath + LogFileName + "_2.log"))
				{
					FString FilePath = XhLogPath + LogFileName + "_2.log";
					FString XhDateString = FDateTime::Now().ToString(TEXT("%Y.%m.%d-%H.%M.%S"));
					FString NewPath = XhLogPath + LogFileName + "-backup-" + XhDateString + ".log";
					IFileManager::Get().Move(*NewPath, *FilePath);
				}
				{
					FString FilePath = XhLogPath + LogFileName + ".log";
					FString NewPath = XhLogPath + LogFileName + "_2.log";
					IFileManager::Get().Move(*NewPath, *FilePath);
				}
			}

		}
	}
}

void AXhGameMode::BeginPlay()
{
	XH_BP_EXEC_B(XhBegin);
	Super::BeginPlay();
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if (AXhCharacter* XhCharacter = Cast<AXhCharacter>(PC->GetPawn()))
		{
			//�Ƿ����ü�������(��VRģʽ)
			if (bEnableKB)
			{
				XhCharacter->InitEnableKB();
			}
		}
	}
	//��־
	if (XhVrSettings)
	{
		if (XhVrSettings->bEnableLog)
		{
			InitLog();
		}
	}
	//DT_ActorTransform->GetAllRows<FActorTransform>(TEXT(""), ActorTransform);
	XH_BP_EXEC_E(XhBegin);
}

