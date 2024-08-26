// Copyright Epic Games, Inc. All Rights Reserved.

#include "Tool/XhTool.h"
#include "XhVr.h"
#include "Runtime/Core/Public/Misc/SecureHash.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "Runtime/Core/Public/HAL/FileManager.h"
#include "Kismet/GameplayStatics.h"
#include "Settings/XhVrSettings.h"
#include "IXRTrackingSystem.h"
#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/PreWindowsApi.h"
#include "cstdlib"
#include <windows.h>//#include "cstdlib"
#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"
#endif
//#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/Engine.h"

UXhVrSettings* UXhTool::XhVrSettings;
UXhTool::UXhTool(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

UXhVrSettings* UXhTool::GetVrSettings()
{
	if (!XhVrSettings)
	{
		XhVrSettings = GetMutableDefault<UXhVrSettings>();
	}
	return XhVrSettings;
	//return GetMutableDefault<UXhVrSettings>();
}

void UXhTool::OpenFile(const FString& FileName, const FString& Parms /*= ""*/)
{
	FPlatformProcess::LaunchFileInDefaultExternalApplication(*FileName, *Parms);
}

void UXhTool::Exe(const FString& URL, const FString& Params, bool bLaunchHidden, bool bLaunchReallyHidden, bool bLaunchDetached /*= true*/)
{
#if PLATFORM_WINDOWS
	FPlatformProcess::CreateProc(*URL, *Params, bLaunchDetached, bLaunchHidden, bLaunchReallyHidden, nullptr, -1, nullptr, nullptr);
#endif
}

void UXhTool::DosCmd(const FString& CmdString)
{
#if PLATFORM_WINDOWS
	system(TCHAR_TO_UTF8(*CmdString));
#endif
}

FString UXhTool::GetCPU_Info()
{
#if PLATFORM_WINDOWS
	return FString::FromInt(FWindowsPlatformMisc::GetCPUInfo());
#else
	return "";
#endif
}

FString UXhTool::GetMac()
{
#if PLATFORM_WINDOWS
	//FGenericPlatformMisc::GetLoginID();
	return FBase64::Encode(FWindowsPlatformMisc::GetMacAddress(), EBase64Mode::Standard);
#else
	return "";
#endif
}

FString UXhTool::GetMD5(const FString& str)
{
	return FMD5::HashAnsiString(*str);
}

bool UXhTool::DeleteFile(const FString& Filename, bool RequireExists /*= false*/, bool EvenReadOnly /*= false*/, bool Quiet /*= false*/)
{
	return IFileManager::Get().Delete(*Filename, RequireExists, EvenReadOnly, Quiet);
}

bool UXhTool::DeleteDirectory(const FString& FilePath, bool RequireExists /*= false*/, bool Tree /*= false*/)
{
	return IFileManager::Get().DeleteDirectory(*FilePath, RequireExists, Tree);
}

bool UXhTool::DoesExistsFile(const FString& FilePath)
{
	return FPaths::FileExists(FilePath);
}

bool UXhTool::DoesExistsDirectory(const FString& DirectoryPath)
{
	return FPaths::DirectoryExists(DirectoryPath);
}

TArray<FString> UXhTool::FindFiles(const FString& FindPath, const FString& Filter /*= TEXT("*")*/, bool SaveFile /*= true*/, bool SaveDirectory /*= true*/)
{
	TArray<FString> FilePathList;
	IFileManager::Get().FindFilesRecursive(FilePathList, *FindPath, *Filter, SaveFile, SaveDirectory);
	return FilePathList;
}

bool UXhTool::CopyFile(const FString& Dest, const FString& Src)
{
	return !IFileManager::Get().Copy(*Dest, *Src);
}

bool UXhTool::MoveFile(const FString& Dest, const FString& Src)
{
	return IFileManager::Get().Move(*Dest, *Src);
}

bool UXhTool::RenameFile(const FString& FilePath, const FString& NewName)
{
	if (FPaths::FileExists(FilePath))
	{
		FString NewPath = FPaths::GetPath(FilePath) + "/" + NewName;
		return IFileManager::Get().Move(*NewPath, *FilePath);
	}
	return false;
}

FFileInfo UXhTool::GetFileOrDirInfo(const FString& FilePath)
{
	FFileInfo FileOrDirInfo;
	FFileStatData Info = IFileManager::Get().GetStatData(*FilePath);
	FileOrDirInfo.CreationTime = Info.CreationTime;
	FileOrDirInfo.AccessTime = Info.AccessTime;
	FileOrDirInfo.ModificationTime = Info.ModificationTime;
	FileOrDirInfo.FileSize = Info.FileSize;
	FileOrDirInfo.bIsDirectory = Info.bIsDirectory;
	FileOrDirInfo.bIsReadOnly = Info.bIsReadOnly;
	return FileOrDirInfo;
}

FString UXhTool::ReadFileToString(const FString& FilePath)
{
	FString Content;
	if (FPaths::FileExists(FilePath))
	{
		FFileHelper::LoadFileToString(Content, *FilePath);
	}
	return Content;
}

TArray<FString> UXhTool::ReadFileToStringArray(const FString& FilePath)
{
	TArray<FString> Content;
	if (FPaths::FileExists(FilePath))
	{
		FFileHelper::LoadFileToStringArray(Content, *FilePath);
	}
	return Content;
}

bool UXhTool::WriteString(const FString& ContentStr, const FString& FilePath, FileWrite Type /*= FileWrite::FILEWRITE_Append*/)
{
	switch (Type)
	{
	case FileWrite::FILEWRITE_None:
		return FFileHelper::SaveStringToFile(ContentStr, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_None);
	case FileWrite::FILEWRITE_NoFail:
		return FFileHelper::SaveStringToFile(ContentStr, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_NoFail);
	case FileWrite::FILEWRITE_NoReplaceExisting:
		return FFileHelper::SaveStringToFile(ContentStr, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_NoReplaceExisting);
	case FileWrite::FILEWRITE_EvenIfReadOnly:
		return FFileHelper::SaveStringToFile(ContentStr, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_EvenIfReadOnly);
	case FileWrite::FILEWRITE_Append:
		return FFileHelper::SaveStringToFile(ContentStr, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
	case FileWrite::FILEWRITE_AllowRead:
		return FFileHelper::SaveStringToFile(ContentStr, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_AllowRead);
	case FileWrite::FILEWRITE_Silent:
		return FFileHelper::SaveStringToFile(ContentStr, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Silent);
	default:
		return true;
	}
}

bool UXhTool::WriteStringArray(const TArray<FString>& ContentStr, const FString& FilePath, FileWrite Type /*= FileWrite::FILEWRITE_Append*/)
{
	switch (Type)
	{
	case FileWrite::FILEWRITE_None:
		return FFileHelper::SaveStringArrayToFile(ContentStr, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_None);
	case FileWrite::FILEWRITE_NoFail:
		return FFileHelper::SaveStringArrayToFile(ContentStr, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_NoFail);
	case FileWrite::FILEWRITE_NoReplaceExisting:
		return FFileHelper::SaveStringArrayToFile(ContentStr, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_NoReplaceExisting);
	case FileWrite::FILEWRITE_EvenIfReadOnly:
		return FFileHelper::SaveStringArrayToFile(ContentStr, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_EvenIfReadOnly);
	case FileWrite::FILEWRITE_Append:
		return FFileHelper::SaveStringArrayToFile(ContentStr, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
	case FileWrite::FILEWRITE_AllowRead:
		return FFileHelper::SaveStringArrayToFile(ContentStr, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_AllowRead);
	case FileWrite::FILEWRITE_Silent:
		return FFileHelper::SaveStringArrayToFile(ContentStr, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Silent);
	default:
		return true;
	}
}

bool UXhTool::SaveDataToArbitraryPath(USaveGame* SaveGameObject, const FString& SavePath, const FString& Extension /*= "pak"*/)
{
	TArray<uint8> ObjectBytes;
	if (UGameplayStatics::SaveGameToMemory(SaveGameObject, ObjectBytes))
	{
		if (ObjectBytes.Num() > 0 && SavePath.Len() > 0)
		{
			FString FullSavePath = SavePath + "." + Extension;
			return FFileHelper::SaveArrayToFile(ObjectBytes, *FullSavePath);
		}
		return false;
	}
	return false;
}

USaveGame* UXhTool::LoadDataFromArbitraryPath(const FString& LoadPath, const FString& Extension /*= "pak"*/)
{
	TArray<uint8> OutSaveData;
	if (LoadPath.Len() > 0)
	{
		FString FullLoadPath = LoadPath + "." + Extension;
		if (FFileHelper::LoadFileToArray(OutSaveData, *FullLoadPath))
		{
			return UGameplayStatics::LoadGameFromMemory(OutSaveData);
		}
		else
		{
			OutSaveData.Reset();
			return nullptr;
		}
	}
	return nullptr;
}

void UXhTool::GetTipArrowDegree(const FTransform& SourceTransform, const FVector& TargetLocation, float& Degree, float& YDegree)
{
	FVector DirectionNormal = (TargetLocation - SourceTransform.GetLocation()).GetSafeNormal();
	FVector RightNormal = SourceTransform.GetUnitAxis(EAxis::Y);
	FVector UpNormal = SourceTransform.GetUnitAxis(EAxis::Z);
	double YDot = DirectionNormal.Dot(RightNormal);
	double ZDot = DirectionNormal.Dot(UpNormal);
	YDegree = (180.0) / UE_DOUBLE_PI * FMath::Acos(YDot);
	Degree = (180.0) / UE_DOUBLE_PI * FMath::Atan(YDot / ZDot);
}

bool UXhTool::StringSetIsEqual(const TSet<FString>& Set1, const TSet<FString>& Set2)
{
	return Set1.CreateConstIterator() == Set2.CreateConstIterator();
}

FTransform UXhTool::ToHMD_Transform(const FTransform& InTransform)
{
	FTransform Result = InTransform;
	FVector Position(0.f);
	if (GEngine->XRSystem.IsValid() && GEngine->XRSystem->IsHeadTrackingAllowed())
	{
		FQuat OrientationAsQuat;

		GEngine->XRSystem->GetCurrentPose(IXRTrackingSystem::HMDDeviceId, OrientationAsQuat, Position);

		//EndRotator = OrientationAsQuat.Rotator();
	}
	else
	{
		return Result;
	}
	FRotator Temp = FRotator(0, InTransform.Rotator().Yaw, 0);
	Result.SetLocation(InTransform.GetLocation() - Temp.RotateVector(FVector(Position.X, Position.Y, 0)));
	return Result;
}

void UXhTool::WriteLog(const UObject* WorldContextObject, const FString& InStringLog, bool bScreen /*= true*/)
{
	/*GetVrSettings()*/

	FString Prefix;
	//DataTime.ToString(TEXT("%Y/%m/%d %H:%M:%S:%s"));//[2024/03/26 16:52:45:587]
	Prefix += "[" + FDateTime::Now().ToString(TEXT("%Y/%m/%d %H:%M:%S:%s")) + "]";
	if (WorldContextObject)
	{
		Prefix += "[" + WorldContextObject->GetFName().ToString() + "] ";
	}

#if DO_BLUEPRINT_GUARD
	if (!FBlueprintContextTracker::Get().GetCurrentScriptStack().IsEmpty())
	{
		const TArrayView<const FFrame* const> ScriptStack = FBlueprintContextTracker::Get().GetCurrentScriptStack();
		Prefix += ScriptStack.Last()->Node->GetName() + ":";
	}
#endif

	FString StringLog = Prefix + InStringLog;
	FString FilePath = GetVrSettings()->LogPath + GetVrSettings()->LogFileName + ".log";
	FFileHelper::SaveStringToFile(StringLog + "\r\n", *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
	if (bScreen)
	{
		UE_LOG(LogTemp, Error, TEXT("%s"), *StringLog);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, StringLog);
	}
}

void UXhTool::PrintLog(const FString& InStringLog)
{
	UE_LOG(LogTemp, Error, TEXT("%s"), *InStringLog);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, InStringLog);
}

