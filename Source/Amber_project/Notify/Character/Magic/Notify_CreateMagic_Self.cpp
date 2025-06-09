// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_CreateMagic_Self.h"

#include "PaperZDAnimInstance.h"
#include "Amber_project/Player/MainPaperZDCharacter.h"
#include "Amber_project/Player/Character/Magic/Wizard_Attack_2.h"

void UNotify_CreateMagic_Self::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (OwningInstance)
	{
		AMainPaperZDCharacter* ZdCharacter = Cast<AMainPaperZDCharacter>(OwningInstance->GetOwningActor());
		
		FActorSpawnParameters Params;
		Params.Owner = ZdCharacter;

		UWorld* World = ZdCharacter->GetWorld();
		if (World && MagicClass)
		{
			//所有的法术好像都可以继承自AWizard_Attack_2
			AWizard_Attack_2* Mag = World->SpawnActor<AWizard_Attack_2>(MagicClass,ZdCharacter->GetActorLocation(),FRotator::ZeroRotator,  Params);
			if (bMovement == false)
			{
				Mag->ProjectileMovementComponent_2->Deactivate();
			}
		}
	}
}
