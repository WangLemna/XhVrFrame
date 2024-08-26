// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Type/XhType.h"
#include "XhTool.generated.h"

class UXhVrSettings;

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/

/*FileInfo*/
USTRUCT(BlueprintType)
struct FFileInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FDateTime CreationTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FDateTime AccessTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FDateTime ModificationTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int64 FileSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsDirectory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsReadOnly;
	FFileInfo()
		: CreationTime(FDateTime::MinValue())
		, AccessTime(FDateTime::MinValue())
		, ModificationTime(FDateTime::MinValue())
		, FileSize(-1)
		, bIsDirectory(false)
		, bIsReadOnly(false)
	{
	}
};

UCLASS()
class XHVR_API UXhTool : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
	static UXhVrSettings* XhVrSettings;
	static UXhVrSettings* GetVrSettings();
public:
#pragma region Tool
	/*ToolBegin*/
	UFUNCTION(BlueprintCallable, meta = (Keywords = "OpenOther"), Category = "XhTool|Tool")
	static void OpenFile(const FString& FileName, const FString& Parms = "");

	UFUNCTION(BlueprintCallable, meta = (Keywords = "Exe"), Category = "XhTool|Tool")
	static void Exe(const FString& URL, const FString& Params, bool bLaunchHidden, bool bLaunchReallyHidden, bool bLaunchDetached = true);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "DosCmd"), Category = "XhTool|Tool")
	static void DosCmd(const FString& CmdString);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "GetCPU_Info"), Category = "XhTool|Tool")
	FString GetCPU_Info();

	UFUNCTION(BlueprintPure, meta = (Keywords = "GetMac"), Category = "XhTool|Tool")
	static FString GetMac();

	UFUNCTION(BlueprintPure, meta = (Keywords = "GetMD5"), Category = "XhTool|Tool")
	static FString GetMD5(const FString& str);
	/*`ToolEnd*/
#pragma endregion

#pragma region File
	/*FlieBegin*/
	UFUNCTION(BlueprintCallable, meta = (Keywords = "DeleteFile"), Category = "XhTool|File")
	static bool DeleteFile(const FString& Filename, bool RequireExists = false, bool EvenReadOnly = false, bool Quiet = false);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "DeleteDirectory"), Category = "XhTool|File")
	static bool	DeleteDirectory(const FString& FilePath, bool RequireExists = false, bool Tree = false);

	UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "DoesExistsFile"), Category = "XhTool|File")
	static bool DoesExistsFile(const FString& FilePath);

	UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "DoesExistsDirectory"), Category = "XhTool|File")
	static bool DoesExistsDirectory(const FString& DirectoryPath);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "FindFiles"), Category = "XhTool|File")
	static TArray<FString> FindFiles(const FString& FindPath, const FString& Filter = TEXT("*"), bool SaveFile = true, bool SaveDirectory = true);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "CopyFile"), Category = "XhTool|File")
	static bool CopyFile(const FString& Dest, const FString& Src);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "MoveFile"), Category = "XhTool|File")
	static bool MoveFile(const FString& Dest, const FString& Src);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "RenameFile"), Category = "XhTool|File")
	static bool RenameFile(const FString& FilePath, const FString& NewName);

	UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "GetFileOrDirInfo"), Category = "XhTool|File")
	static FFileInfo GetFileOrDirInfo(const FString& FilePath);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "ReadFileToString"), Category = "XhTool|File")
	static FString ReadFileToString(const FString& FilePath);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "ReadFileToStringArray"), Category = "XhTool|File")
	static TArray<FString> ReadFileToStringArray(const FString& FilePath);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "WriteStringFile"), Category = "XhTool|File")
	static bool WriteString(const FString& ContentStr, const FString& FilePath, FileWrite Type = FileWrite::FILEWRITE_Append);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "WriteStringArrayFile"), Category = "XhTool|File")
	static bool WriteStringArray(const TArray<FString>& ContentStr, const FString& FilePath, FileWrite Type = FileWrite::FILEWRITE_Append);
	/*FileEnd*/
#pragma endregion

#pragma region UE_SaveGame
	/*UnrealEngine SaveGame Begin*/
	UFUNCTION(BlueprintCallable, meta = (Keywords = "SaveDataToArbitraryPath"), Category = "XhTool|SaveGame")
	static bool SaveDataToArbitraryPath(USaveGame* SaveGameObject, const FString& SavePath, const FString& Extension = "pak");

	UFUNCTION(BlueprintCallable, meta = (Keywords = "LoadDataFromArbitraryPath"), Category = "XhTool|SaveGame")
	static USaveGame* LoadDataFromArbitraryPath(const FString& LoadPath, const FString& Extension = "pak");
	/*`UnrealEngine SaveGame End*/
#pragma endregion

#pragma region XhMath
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "GetArrowDirection"), Category = "XhTool|XhMath")
	static void GetTipArrowDegree(const FTransform& SourceTransform, const FVector& TargetLocation, float& Degree, float& YDegree);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "StringSetIsEqual"), Category = "XhTool|XhMath")
	static bool StringSetIsEqual(const TSet<FString>& Set1, const TSet<FString>& Set2);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "ToHMDTransform"), Category = "XhTool|XhMath")
	static FTransform ToHMD_Transform(const FTransform& InTransform);
#pragma endregion
	UFUNCTION(BlueprintCallable, meta = (Keywords = "WriteLog", WorldContext = "WorldContextObject"), Category = "XhTool|XhLog")
	static void WriteLog(const UObject* WorldContextObject, const FString& InStringLog, bool bScreen = true);
	UFUNCTION(BlueprintCallable, meta = (Keywords = "PrintLog"), Category = "XhTool|XhLog")
	static void PrintLog(const FString& InStringLog);
};



