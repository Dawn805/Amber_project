// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_AttackBox.h"

#include "PaperZDAnimInstance.h"
#include "Amber_project/Enemy/MainPaperZDEnemy.h"
#include "Amber_project/Player/MainPaperZDCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

void UNotify_AttackBox::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (!OwningInstance)
	{
		FVector Location = SequenceRenderComponent->GetComponentLocation();
		if (SocketName != "No") Location = SequenceRenderComponent->GetSocketLocation(SocketName);

		DrawDebugBox(this->GetWorld(),Location,BoxExtent,BoxColor,false,2);
	}

	else
	{
		FVector Location = SequenceRenderComponent->GetComponentLocation();
		if (SocketName != "No") Location = SequenceRenderComponent->GetSocketLocation(SocketName);
		
		AMainPaperZDCharacter* Player = Cast<AMainPaperZDCharacter>(OwningInstance->GetPaperCharacter());
		if (!Player) return;

		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(Player);

		TArray<class AActor*> OutActors;
		
		bool bHit = UKismetSystemLibrary::BoxOverlapActors(
			Player->GetWorld(),
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
				if (Cast<AMainPaperZDEnemy>(OverlapActor))
				{
					AMainPaperZDEnemy* Enemies = Cast<AMainPaperZDEnemy>(OverlapActor);

					float Hurt = Player->StateComponent->Damage * AttackDamage_Mult - Enemies->Defense;
					if (Hurt > 0)
					{
						Enemies->HP -= Hurt;
					}
					Enemies->Poise -= BreakPoise;
				}
			}
		}
	}
}
