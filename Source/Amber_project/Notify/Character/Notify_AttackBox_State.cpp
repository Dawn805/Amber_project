// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify_AttackBox_State.h"

#include "PaperZDAnimInstance.h"
#include "Amber_project/Player/MainPaperZDCharacter.h"
#include "Kismet/GameplayStatics.h"

void UNotify_AttackBox_State::OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Enemies.Empty();
}

void UNotify_AttackBox_State::OnNotifyTick_Implementation(float DeltaTime, UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyTick_Implementation(DeltaTime, OwningInstance);

	if (!OwningInstance)
	{
		FVector Location = SequenceRenderComponent->GetComponentLocation();
		if (SocketName != "No") Location = SequenceRenderComponent->GetSocketLocation(SocketName);
		DrawDebugBox(this->GetWorld(),Location,BoxExtent,FColor::Red,false,2);
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

		bool bHit = UKismetSystemLibrary::BoxOverlapActors(
			GetWorld(),
			Location,
			BoxExtent,
			ObjectTypes,
			nullptr,
			ActorsToIgnore,
			OutActors);

		if (bHit)
		{
			for (int i = 0 ; i < OutActors.Num(); i++)
			{
				AActor* OverlapActor = OutActors[i];
				if (Cast<AMainPaperZDEnemy >(OverlapActor))
				{
					AMainPaperZDEnemy* ZdEnemy = Cast<AMainPaperZDEnemy>(OverlapActor);

					if (Enemies.Contains(ZdEnemy))
					{
						continue;
					}
					
					float Hurt = ZdCharacter->StateComponent->Damage * AttackDamage_Mult - ZdEnemy->Defense;
					if (Hurt > 0)
					{
						ZdEnemy->HP -= Hurt;
					}
					ZdEnemy->Poise -= BreakPoise;

					Enemies.Add(ZdEnemy);
				}
			}
		}
	}
}

void UNotify_AttackBox_State::OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Enemies.Empty();
}
