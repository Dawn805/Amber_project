// Fill out your copyright notice in the Description page of Project Settings.


#include "Magic_Destory.h"

#include "PaperZDAnimInstance.h"
#include "Amber_project/Player/Character/Magic/Wizard_Attack_2.h"

void UMagic_Destory::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (!OwningInstance) return;

	AWizard_Attack_2* Mag = Cast<AWizard_Attack_2>(OwningInstance->GetOwningActor());
	if (!Mag) return;

	Mag->Destroy();
}
