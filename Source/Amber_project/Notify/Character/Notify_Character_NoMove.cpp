// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_Character_NoMove.h"

#include "PaperZDAnimInstance.h"
#include "Amber_project/Player/MainPaperZDCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UNotify_Character_NoMove::OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (!OwningInstance) return;

	AMainPaperZDCharacter* ZDCharacter = Cast<AMainPaperZDCharacter>(OwningInstance->GetPaperCharacter());
	if (!ZDCharacter) return;
	
	ZDCharacter->GetCharacterMovement()->MaxWalkSpeed = BeginSpeed;

}

void UNotify_Character_NoMove::OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (!OwningInstance) return;

	AMainPaperZDCharacter* ZdCharacter = Cast<AMainPaperZDCharacter>(OwningInstance->GetPaperCharacter());
	if (!ZdCharacter) return;
	
	ZdCharacter->GetCharacterMovement()->MaxWalkSpeed = EndSpeed;

}
