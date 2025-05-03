// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_Character_AnimLocked.h"

#include "PaperZDAnimInstance.h"
#include "Amber_project/Player/MainPaperZDCharacter.h"

void UNotify_Character_AnimLocked::OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (!OwningInstance) return;

	AMainPaperZDCharacter* ZdCharacter = Cast<AMainPaperZDCharacter>(OwningInstance->GetPaperCharacter());
	if (!ZdCharacter) return;

	ZdCharacter->AnimRight = false;
}

void UNotify_Character_AnimLocked::OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (!OwningInstance) return;

	AMainPaperZDCharacter* ZdCharacter = Cast<AMainPaperZDCharacter>(OwningInstance->GetPaperCharacter());
	if (!ZdCharacter) return;

	ZdCharacter->AnimRight = true;;
}
