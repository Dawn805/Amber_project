// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_Enemy_AnimLocked.h"

#include "PaperZDAnimInstance.h"
#include "Amber_project/Enemy/MainPaperZDEnemy.h"

void UNotify_Enemy_AnimLocked::OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (!OwningInstance) return;

	AMainPaperZDEnemy* Enemy = Cast<AMainPaperZDEnemy>(OwningInstance->GetPaperCharacter());
	if (!Enemy) return;
	Enemy->AnimRight = false;
}

void UNotify_Enemy_AnimLocked::OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (!OwningInstance) return;

	AMainPaperZDEnemy* Enemy = Cast<AMainPaperZDEnemy>(OwningInstance->GetPaperCharacter());
	if (!Enemy) return;
	Enemy->AnimRight = true;
	Enemy->Poise = Enemy->MaxPoise;
}
