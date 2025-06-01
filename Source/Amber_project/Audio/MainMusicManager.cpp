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

void UMainMusicManager::OnWorldBeginPlay(UWorld& InWorld)
{
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
			AudioComponent->FadeIn(whenin,VSettings.BGMVolume*VSettings.MasterVolume);
			CurrentSound = Sound;
		}
	}
}

//这个Sort好像没啥用，算了，写都写了
void UMainMusicManager::BGMs_Sort()
{
	BGMs.Sort([](const FAudioBGM& A , const FAudioBGM& B)
	{
		return A.Priority > B.Priority;
	});
}

void UMainMusicManager::PlayNewBGM(FAudioBGM NewBGM)
{
	int sum = BGMs.Num();
	
	//如果数组里面啥都没有，就直接Add插入
	if (sum == 0)
	{
		BGMs.Add(NewBGM);
		UAudioComponent* NewAudioComponent = UGameplayStatics::SpawnSound2D(GetWorld(),NewBGM.BGM,1);
		if (NewAudioComponent)
		{
			AudioComponent = NewAudioComponent;
			AudioComponent->FadeIn(BGMs[0].FadeInTime,1);
		}
		return;
	}

	//如果新加入的音频的优先级比当前播放的优先级小，如果列表没有当前音频，就放后面去不管，如果有，就更不管了
	if (NewBGM.Priority < BGMs[0].Priority)
	{
		int BGMs_Insert = sum;
		bool sub = true;
		for (int i = 0 ; i < sum ; i++)
		{
			if (BGMs[i].Priority >= NewBGM.Priority)
			{
				if (sub)
				{
					BGMs_Insert = i;
					sub = false;
				}
			}
			if (NewBGM.BGM == BGMs[i].BGM)
			{
				return;
			}
		}
		BGMs.Insert(NewBGM,BGMs_Insert);
		return;
	}

	//如果新加入的音频优先级和当前播放的一样，如果列表里面有，那就删掉列表中的音频并且在开头加上新音频，如果没有，就直接加上
	if (NewBGM.Priority == BGMs[0].Priority)
	{
		for (int i = 0 ; i < sum ; i++)
		{
			if (BGMs[i].BGM == NewBGM.BGM)
			{
				BGMs.RemoveAt(i);
			}
		}
		BGMs.Insert(NewBGM,0);

		//开始淡入淡出音频
		AudioComponent->FadeOut(BGMs[1].FadeOutTime,0.0f);
		AudioComponent->GetOwner()->SetLifeSpan(BGMs[1].FadeOutTime+0.5f);
		AudioComponent = nullptr;

		UAudioComponent* NewAudioComponent = UGameplayStatics::SpawnSound2D(GetWorld(),NewBGM.BGM,1);
		if (NewAudioComponent)
		{
			AudioComponent = NewAudioComponent;
			AudioComponent->FadeIn(BGMs[0].FadeInTime,1);
		}
		return;
	}

	//如果新加入的音频优先级比当前的大，那很有生活了
	if (NewBGM.Priority > BGMs[0].Priority)
	{
		BGMs.Insert(NewBGM,0);
		
		AudioComponent->FadeOut(BGMs[1].FadeOutTime,0.0f);
		AudioComponent->GetOwner()->SetLifeSpan(BGMs[1].FadeOutTime+0.5f);
		AudioComponent = nullptr;

		UAudioComponent* NewAudioComponent = UGameplayStatics::SpawnSound2D(GetWorld(),NewBGM.BGM,1);
		if (NewAudioComponent)
		{
			AudioComponent = NewAudioComponent;
			AudioComponent->FadeIn(BGMs[0].FadeInTime,1);
		}
	}
}

void UMainMusicManager::DeleteOldBGM(FAudioBGM OldBGM)
{
	//如果OldBGM不是当前正在播放的BGM，那很好了，很省事了
	if (OldBGM.BGM != BGMs[0].BGM)
	{
		for (int i = 0 ; i < BGMs.Num() ; i++)
		{
			if (BGMs[i].BGM == OldBGM.BGM)
			{
				BGMs.RemoveAt(i);
			}
		}
		return;
	}

	//如果OldBGM是当前正在播放的BGM，那很糟糕了，要淡入淡出了
	BGMs.RemoveAt(0);
	AudioComponent->FadeOut(OldBGM.FadeOutTime,0.0f);
	AudioComponent->GetOwner()->SetLifeSpan(OldBGM.FadeOutTime+0.5f);
	AudioComponent = nullptr;

	if (BGMs.Num() != 0)
	{
		UAudioComponent* NewAudioComponent = UGameplayStatics::SpawnSound2D(GetWorld(),BGMs[0].BGM,1);
		if (NewAudioComponent)
		{
			AudioComponent = NewAudioComponent;
			AudioComponent->FadeIn(BGMs[0].FadeInTime,1);
		}
	}
}

void UMainMusicManager::PlayDisposableBGM(FAudioBGM NewBGM)
{
	if (AudioComponent && BGMs.Num() != 0)
	{
		AudioComponent->FadeOut(BGMs[0].FadeOutTime,0.0f);
		AudioComponent->GetOwner()->SetLifeSpan(BGMs[0].FadeOutTime+0.5f);
		AudioComponent = nullptr;
	}

	BGMs.Insert(NewBGM,0);

	UAudioComponent* NewAudioComponent = UGameplayStatics::SpawnSound2D(GetWorld(),BGMs[0].BGM,1);
	if (NewAudioComponent)
	{
		AudioComponent = NewAudioComponent;
		AudioComponent->FadeIn(BGMs[0].FadeInTime,1);
		AudioComponent->OnAudioFinished.AddDynamic(this,&UMainMusicManager::OnDisposableBGMFinished);
	}
}

void UMainMusicManager::OnDisposableBGMFinished()
{
	DeleteOldBGM(BGMs[0]);
}


