// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameUserSettings.h"

FWindowsSettings UMainGameUserSettings::GetWindowsSettings()
{
	return this->WindowsSettings;
}

void UMainGameUserSettings::UpdateWindowSettings(FWindowsSettings& NewSettings)
{
	
	WindowsSettings = NewSettings;

	SetFullscreenMode(static_cast<EWindowMode::Type>(WindowsSettings.WindowMode));
	SetFrameRateLimit(WindowsSettings.WindowFPS);
	SetScreenResolution(WindowsSettings.WindowSize);
	SetVSyncEnabled(WindowsSettings.WindowSync);

	ApplySettings(false);

	SaveSettings();
	
}
