// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_Enemy_NoMove.h"

#include "PaperZDAnimInstance.h"
#include "Amber_project/Enemy/MainPaperZDEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"

void UNotify_Enemy_NoMove::OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (!OwningInstance) return;
	AMainPaperZDEnemy* ZDEnemy = Cast<AMainPaperZDEnemy>(OwningInstance->GetPaperCharacter());
	if (!ZDEnemy) return;

	ZDEnemy->GetCharacterMovement()->MaxWalkSpeed = 0;
}

void UNotify_Enemy_NoMove::OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (!OwningInstance) return;
	AMainPaperZDEnemy* ZDEnemy = Cast<AMainPaperZDEnemy>(OwningInstance->GetPaperCharacter());
	if (!ZDEnemy) return;

	ZDEnemy->GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
}

