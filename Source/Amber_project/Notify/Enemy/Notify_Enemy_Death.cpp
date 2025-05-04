// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_Enemy_Death.h"

#include "PaperZDAnimInstance.h"
#include "Amber_project/Enemy/MainPaperZDEnemy.h"

void UNotify_Enemy_Death::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (!OwningInstance) return;

	AMainPaperZDEnemy* Enemy = Cast<AMainPaperZDEnemy>(OwningInstance->GetPaperCharacter());
	if (!Enemy) return;

	Enemy->SetActorTickEnabled(false);
	Enemy->InitialLifeSpan = 3.0f;
}
