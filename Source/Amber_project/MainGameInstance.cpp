// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "SaveGame/VolumeSave.h"

void UMainGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UMainGameInstance::OnPostLoadMap);
}

void UMainGameInstance::OnPostLoadMap(UWorld* LoadedWorld)
{
	UVolumeSave* Settings = GetMutableDefault<UVolumeSave>();

	if (Settings && SoundMix && SoundClass_Master && SoundClass_BGM && SoundClass_Sound)
	{
		UGameplayStatics::SetSoundMixClassOverride(LoadedWorld, SoundMix, SoundClass_Master, Settings->MasterVolumeValue, 1, 1, true);
		UGameplayStatics::SetSoundMixClassOverride(LoadedWorld, SoundMix, SoundClass_BGM, Settings->BGMVolumeValue, 1, 1, true);
		UGameplayStatics::SetSoundMixClassOverride(LoadedWorld, SoundMix, SoundClass_Sound, Settings->SoundVolumeValue, 1, 1, true);
		UGameplayStatics::PushSoundMixModifier(LoadedWorld, SoundMix);
	}
}

