// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"
#include "PlatformFilemanager.h"
#include "FileHelper.h"

bool UMyBlueprintFunctionLibrary::DeleteFile(FString FilePath)
{
	return IFileManager::Get().Delete(*FilePath);
}
FString UMyBlueprintFunctionLibrary::GetFileContent( FString Filepath, FString Extension)
{
	TArray<FString>DirsArray;
	//�ļ���·��
	FString filecontents;
	TSharedRef <TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&filecontents);
	JsonWriter->WriteObjectStart(); // �൱��д��һ����
	JsonWriter->WriteObjectStart("content"); // �൱��д��һ��"TestData": �ͣ�
	FString SearchedFiles = Filepath + "/" + TEXT("*");
	//����Filepath��·���µ��ļ���
	IFileManager::Get().FindFiles(DirsArray, *SearchedFiles, false, true);
	//�����ļ�
	//IFileManager::Get().FindFiles(DirsArray, *SearchedFiles, true, false);
	for (size_t i = 0; i < DirsArray.Num(); i++)
	{
		FString filePath = Filepath + "/" + DirsArray[i] + "/";
		FString fileWithExtension = filePath + Extension;
		//UE_LOG(LogTemp, Error, TEXT("TARRAY____%s"), *DirsArray[i]);
		//UE_LOG(LogTemp, Error, TEXT("�ļ���____%s"), *fileWithExtension);
		//GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, Filepath);
		TArray<FString>filesArray;
		IFileManager::Get().FindFiles(filesArray, *fileWithExtension, true, false);
		JsonWriter->WriteArrayStart(DirsArray[i]); // �൱��д��һ��"Hobby": ��[
		for (size_t j = 0; j < filesArray.Num(); j++)
		{
			
			JsonWriter->WriteValue(filesArray[j]); // �൱��д��һ��"Reading"
			//FString fileFullName = filePath + filesArray[j];
			//UE_LOG(LogClass, Error, TEXT("���ļ���...%s"), *fileFullName);
			//GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, fileFullName);
		}
		JsonWriter->WriteArrayEnd(); // �൱��д��һ��]

	}
	JsonWriter->WriteObjectEnd();
	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();
	return filecontents;
}
