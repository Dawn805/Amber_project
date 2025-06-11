// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_Enemy_BossDeath.h"

#include "Amber_project/Audio/MainMusicManager.h"

void UNotify_Enemy_BossDeath::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (!OwningInstance) return;
	UMainMusicManager* MusicManager = GetWorld()->GetSubsystem<UMainMusicManager>();
	if (MusicManager)
	{
		FAudioBGM NewBGM;
		NewBGM.Priority = 3;
		NewBGM.BGM = DeathSound;
		NewBGM.FadeInTime = 1.0f;
		NewBGM.FadeOutTime = 1.0f;
            
		MusicManager->PlayDisposableBGM(NewBGM);
	}
}
