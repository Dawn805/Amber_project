// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_Enemy_JumpToHurt.h"

#include "PaperZDAnimInstance.h"
#include "Amber_project/Enemy/MainPaperZDEnemy.h"

void UNotify_Enemy_JumpToHurt::OnNotifyTick_Implementation(float DeltaTime, UPaperZDAnimInstance* OwningInstance) const
{
	if (!OwningInstance) return;

	AMainPaperZDEnemy* Enemy = Cast<AMainPaperZDEnemy>(OwningInstance->GetPaperCharacter());
	if (!Enemy) return;

	if (Enemy->Poise > 0) return;

	UPaperZDAnimInstance* ZdAnimInstance = Cast<UPaperZDAnimInstance>(Enemy->GetAnimInstance());
	if (!ZdAnimInstance) return;

	Enemy->Poise = Enemy->MaxPoise;
	ZdAnimInstance->JumpToNode("Hurt","Locomotion");
}
