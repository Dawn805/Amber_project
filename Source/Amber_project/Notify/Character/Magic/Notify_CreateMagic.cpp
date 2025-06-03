// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_CreateMagic.h"

#include <SceneExport.h>

#include "PaperZDAnimInstance.h"
#include "Amber_project/Player/MainPaperZDCharacter.h"

void UNotify_CreateMagic::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (!OwningInstance) return;

	AMainPaperZDCharacter* ZdCharacter = Cast<AMainPaperZDCharacter>(OwningInstance->GetPaperCharacter());
	if (!ZdCharacter) return;

	float Direction = 1.0f;
	if (ZdCharacter)
	{
		Direction = ZdCharacter->FaceDirection;
	}

	FVector SpawnLocation = ZdCharacter->GetActorLocation() + FVector(Location*Direction,0,0);

	FActorSpawnParameters Params;
	Params.Owner = ZdCharacter;

	UWorld* World = ZdCharacter->GetWorld();
	if (World && MagicClass)
	{
		AActor* Mag = World->SpawnActor<AActor>(MagicClass,SpawnLocation,FRotator::ZeroRotator,  Params);
	}
}
