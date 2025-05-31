// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_Enemy_AITreeBeginAndEnd.h"

#include "PaperZDAnimInstance.h"
#include "Amber_project/Enemy/MainPaperZDEnemy.h"

void UNotify_Enemy_AITreeBeginAndEnd::OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (!OwningInstance) return;

	AMainPaperZDEnemy* Enemy = Cast<AMainPaperZDEnemy>(OwningInstance->GetPaperCharacter());
	if (!Enemy) return;

	Enemy->AITree_End();
}

void UNotify_Enemy_AITreeBeginAndEnd::OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (!OwningInstance) return;

	AMainPaperZDEnemy* Enemy = Cast<AMainPaperZDEnemy>(OwningInstance->GetPaperCharacter());
	if (!Enemy) return;

	if (Enemy->HP > 0) Enemy->AITree_Begin();
}
