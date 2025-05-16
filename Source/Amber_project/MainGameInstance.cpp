// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/VolumeSave.h"

void UMainGameInstance::Init()
{
	Super::Init();

	FIntPoint NewResolution = FIntPoint(1920, 1080);
	EWindowMode::Type WindowMode = EWindowMode::WindowedFullscreen;

	GEngine->GameUserSettings->SetScreenResolution(NewResolution);
	GEngine->GameUserSettings->SetFullscreenMode(WindowMode);

	GEngine->SetMaxFPS(60);

	GEngine->GameUserSettings->SetVSyncEnabled(true);

	GEngine->GameUserSettings->ApplySettings(false);
}

