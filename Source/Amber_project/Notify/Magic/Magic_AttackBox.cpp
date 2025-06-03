// Fill out your copyright notice in the Description page of Project Settings.


#include "Magic_AttackBox.h"

#include "Kismet/KismetSystemLibrary.h"

void UMagic_AttackBox::OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Enemies.Empty();
}

void UMagic_AttackBox::OnNotifyTick_Implementation(float DeltaTime, UPaperZDAnimInstance* OwningInstance) const
{
	
}

void UMagic_AttackBox::OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Enemies.Empty();
}
