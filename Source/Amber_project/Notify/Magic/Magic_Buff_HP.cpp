// Fill out your copyright notice in the Description page of Project Settings.


#include "Magic_Buff_HP.h"

#include "PaperZDAnimInstance.h"
#include "Amber_project/MainPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UMagic_Buff_HP::OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (OwningInstance)
	{
		AMainPlayerController* PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (PlayerController)
		{
			PlayerController->CurrentCharacter->StateComponent->HP += HP_Current;
			PlayerController->AnotherCharacter->StateComponent->HP += HP_Another;
		}
	}
}

void UMagic_Buff_HP::OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (OwningInstance)
	{
		OwningInstance->GetOwningActor()->Destroy();
	}
}

