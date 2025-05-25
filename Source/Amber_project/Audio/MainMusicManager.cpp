// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMusicManager.h"

#include "Amber_project/SaveGame/MainGameUserSettings.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

TStatId UMainMusicManager::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UMainMusicManager,STATGROUP_Tickables);
}

void UMainMusicManager::PostInitialize()
{
	SoundMix = LoadObject<USoundMix>(this,TEXT("/Game/Sound_0/SoundMix_0.SoundMix_0"));
	SoundClass_Master = LoadObject<USoundClass>(this,TEXT("/Game/Sound_0/MasterVolume_0.MasterVolume_0"));
	SoundClass_BGM = LoadObject<USoundClass>(this,TEXT("/Game/Sound_0/BGMVolume_0.BGMVolume_0"));
	SoundClass_Sound = LoadObject<USoundClass>(this,TEXT("/Game/Sound_0/SoundVolume_0.SoundVolume_0"));

	ApplyVolume();
}

void UMainMusicManager::ApplyVolume()
{
	UMainGameUserSettings* UserSettings = Cast<UMainGameUserSettings>(GEngine->GetGameUserSettings());
	FVolumeSettings VSettings = UserSettings->GetVolumeSettings();
	UWorld* World = GetWorld();

	if (!World) return;

	UGameplayStatics::SetSoundMixClassOverride(World,SoundMix,SoundClass_Master,VSettings.MasterVolume,1,0,true);
	UGameplayStatics::SetSoundMixClassOverride(World,SoundMix,SoundClass_BGM,VSettings.BGMVolume,1,0,true);
	UGameplayStatics::SetSoundMixClassOverride(World,SoundMix,SoundClass_Sound,VSettings.SoundVolume,1,0,true);
	UGameplayStatics::PushSoundMixModifier(World,SoundMix);
}

void UMainMusicManager::PlaySound(USoundBase* Sound,float whenout,float whenin)
{
	if (Sound == nullptr)
	{
		if (AudioComponent != nullptr)
		{
			AudioComponent->FadeOut(whenout,0.0f);
			AudioComponent->GetOwner()->SetLifeSpan(whenout+0.5f);
			AudioComponent = nullptr;
		}
		CurrentSound = nullptr;
		return;
	}

	if (Sound == CurrentSound) return;

	if (Sound != CurrentSound)
	{
		if (AudioComponent != nullptr)
		{
			AudioComponent->FadeOut(whenout,0.0f);
			AudioComponent->GetOwner()->SetLifeSpan(whenout+0.5f);
			AudioComponent = nullptr;
		}

		UMainGameUserSettings* UserSettings = Cast<UMainGameUserSettings>(GEngine->GetGameUserSettings());
		FVolumeSettings VSettings = UserSettings->GetVolumeSettings();
		
		UAudioComponent* NewAudioComponent = UGameplayStatics::SpawnSound2D(GetWorld(),Sound,1);
		if (NewAudioComponent)
		{
			AudioComponent = NewAudioComponent;
			AudioComponent->FadeIn(whenin,VSettings.BGMVolume*VSettings.MasterVolume+0.01);
			CurrentSound = Sound;
		}
	}
}

