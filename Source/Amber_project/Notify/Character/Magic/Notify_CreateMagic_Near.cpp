// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_CreateMagic_Near.h"

#include "PaperZDAnimInstance.h"
#include "Amber_project/Enemy/MainPaperZDEnemy.h"
#include "Amber_project/Player/MainPaperZDCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UNotify_CreateMagic_Near::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (!OwningInstance)
	{
		FVector Location = SequenceRenderComponent->GetComponentLocation();
		if (SocketName != "No") Location = SequenceRenderComponent->GetSocketLocation(SocketName);
		DrawDebugBox(this->GetWorld(),Location,Boxtent,FColor::Red,false,2);
	}
	else
	{
		AMainPaperZDCharacter* ZdCharacter = Cast<AMainPaperZDCharacter>(OwningInstance->GetOwningActor());
		
		FVector Location = SequenceRenderComponent->GetComponentLocation();
		if (SocketName != "No") Location = SequenceRenderComponent->GetSocketLocation(SocketName);

		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

		TArray<AActor*> ActorsToIgnore;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMainPaperZDCharacter::StaticClass(),ActorsToIgnore);

		TArray<AActor*> OutActors;
		
		bool bHaveEnemy = UKismetSystemLibrary::BoxOverlapActors(
			this->GetWorld(),
			Location,
			Boxtent,
			ObjectTypes,
			nullptr,
			ActorsToIgnore,
			OutActors
			);

		float MinD = TNumericLimits<float>::Max();
		FVector SpawnLocation = {0,0,0};

		if (bHaveEnemy)
		{
			for (int i = 0 ; i < OutActors.Num(); i++)
			{
				if (Cast<AMainPaperZDEnemy>(OutActors[i]))
				{
					AMainPaperZDEnemy* ZdEnemy = Cast<AMainPaperZDEnemy>(OutActors[i]);
					float D2 = FVector::DistSquared(ZdEnemy->GetActorLocation(), ZdCharacter->GetActorLocation());
					if (D2 < MinD)
					{
						MinD = D2;
						SpawnLocation = ZdEnemy->GetActorLocation();
					}
				}
			}
			
			FActorSpawnParameters Params;
			Params.Owner = ZdCharacter;

			UWorld* World = ZdCharacter->GetWorld();
			if (World && MagicClass)
			{
				AActor* Mag = World->SpawnActor<AActor>(MagicClass,SpawnLocation,FRotator::ZeroRotator,  Params);
			}
		}
	}
}
