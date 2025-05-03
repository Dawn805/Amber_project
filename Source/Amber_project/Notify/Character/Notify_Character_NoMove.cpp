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

	FVector Vel = ZDCharacter->GetVelocity();
	// if (ZDCharacter->GetCharacterMovement() && Vel.Z == 0.0f)
	// {
		ZDCharacter->GetCharacterMovement()->MaxWalkSpeed = BeginSpeed;
	// }
}

void UNotify_Character_NoMove::OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (!OwningInstance) return;

	AMainPaperZDCharacter* ZdCharacter = Cast<AMainPaperZDCharacter>(OwningInstance->GetPaperCharacter());
	if (!ZdCharacter) return;

	FVector Vel = ZdCharacter->GetVelocity();
	// if (ZdCharacter->GetCharacterMovement() && Vel.Z == 0.0f)
	// {
		ZdCharacter->GetCharacterMovement()->MaxWalkSpeed = EndSpeed;
	// }
}
