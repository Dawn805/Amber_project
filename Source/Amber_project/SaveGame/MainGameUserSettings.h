// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "MainGameUserSettings.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FWindowsSettings
{
	GENERATED_BODY()

public:
	//0是全屏，1是无边框全屏，2是窗口
	UPROPERTY(VisibleAnywhere, Config)
	int WindowMode = 2;

	//刷新率
	UPROPERTY(VisibleAnywhere, Config)
	int WindowFPS = 60;

	//分辨率
	UPROPERTY(VisibleAnywhere, Config)
	FIntPoint WindowSize = FIntPoint(1024,720);

	//垂直同步
	UPROPERTY(VisibleAnywhere, Config)
	bool WindowSync = true;

	friend bool operator==(const FWindowsSettings& lhs, const FWindowsSettings& rhs)
	{
		return lhs.WindowMode == rhs.WindowMode && lhs.WindowFPS == rhs.WindowFPS && lhs.WindowSize == rhs.WindowSize && lhs.WindowSync == rhs.WindowSync;
	}

	friend bool operator!=(const FWindowsSettings& lhs, const FWindowsSettings& rhs)
	{
		return !(lhs == rhs);
	}

};



UCLASS(BlueprintType)
class AMBER_PROJECT_API UMainGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
    FWindowsSettings WindowsSettings;

	UFUNCTION(BlueprintCallable)
	FWindowsSettings GetWindowsSettings();

	UFUNCTION(BlueprintCallable)
	void UpdateWindowSettings(FWindowsSettings& NewSettings);
};
