// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/MainGameUserSettings.h"

void UMainGameInstance::Init()
{
	Super::Init();

	UMainGameUserSettings* Settings = Cast<UMainGameUserSettings>(GEngine->GetGameUserSettings());
	if (Settings)
	{
		FWindowsSettings WSettings = Settings->GetWindowsSettings();

		Settings->SetFullscreenMode(static_cast<EWindowMode::Type>(WSettings.WindowMode));
		Settings->SetFrameRateLimit(WSettings.WindowFPS);
		Settings->SetScreenResolution(WSettings.WindowSize);
		Settings->SetVSyncEnabled(WSettings.WindowSync);
		
		Settings->ApplySettings(false);
	}
}

