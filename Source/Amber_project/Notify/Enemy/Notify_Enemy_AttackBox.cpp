// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_Enemy_AttackBox.h"

#include "PaperZDAnimInstance.h"
#include "Amber_project/Enemy/MainPaperZDEnemy.h"
#include "Amber_project/Player/MainPaperZDCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UNotify_Enemy_AttackBox::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (!OwningInstance)
	{
		FVector Location = SequenceRenderComponent->GetComponentLocation();
		if (SocketName != "No") Location = SequenceRenderComponent->GetSocketLocation(SocketName);
		DrawDebugBox(this->GetWorld(),Location,BoxExtent,FColor::Red,false,2);
	}
	else
	{
		AMainPaperZDEnemy* Enemy = Cast<AMainPaperZDEnemy>(OwningInstance->GetOwningActor());
		
		FVector Location = SequenceRenderComponent->GetComponentLocation();
		if (SocketName != "No") Location = SequenceRenderComponent->GetSocketLocation(SocketName);

		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

		TArray<AActor*> ActorsToIgnore;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMainPaperZDEnemy::StaticClass(),ActorsToIgnore);

		TArray<AActor*> OutActors;
		
		bool bHit = UKismetSystemLibrary::BoxOverlapActors(
			GetWorld(),
			Location,
			BoxExtent,
			ObjectTypes,
			nullptr,
			ActorsToIgnore,
			OutActors
			);

		if (bHit)
		{
			for (int i = 0 ; i < OutActors.Num() ; i++)
			{
				AActor* OverlapActor = OutActors[i];
				if (Cast<AMainPaperZDCharacter>(OverlapActor))
				{
					AMainPaperZDCharacter* ZdCharacter = Cast<AMainPaperZDCharacter>(OverlapActor);
					if (ZdCharacter)
					{
						float hurt = AttackDamage_Mult * Enemy->Damage - ZdCharacter->StateComponent->Defense;
						if (hurt > 0)
						{
							ZdCharacter->StateComponent->HP -= hurt;
						}
					}
				}
			}
		}
	}
}
