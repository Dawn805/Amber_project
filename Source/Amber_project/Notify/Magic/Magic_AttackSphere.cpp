// Fill out your copyright notice in the Description page of Project Settings.


#include "Magic_AttackSphere.h"

#include "PaperZDAnimInstance.h"
#include "Amber_project/Player/MainPaperZDCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMagic_AttackSphere::OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Enemies.Empty();
}

void UMagic_AttackSphere::OnNotifyTick_Implementation(float DeltaTime, UPaperZDAnimInstance* OwningInstance) const
{
	if (!OwningInstance)
	{
		FVector Location = SequenceRenderComponent->GetComponentLocation();
		if (SocketName != "No") Location = SequenceRenderComponent->GetSocketLocation(SocketName);
		DrawDebugSphere(this->GetWorld(),Location,Radius,12, FColor::Red,false,2);
	}
	else
	{
		AActor* MyActor = OwningInstance->GetOwningActor();
		AMainPaperZDCharacter* ZdCharacter = Cast<AMainPaperZDCharacter>(MyActor->Owner);
		
		FVector Location = SequenceRenderComponent->GetComponentLocation();
		if (SocketName != "No") Location = SequenceRenderComponent->GetSocketLocation(SocketName);

		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

		TArray<AActor*> ActorsToIgnore;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMainPaperZDCharacter::StaticClass(),ActorsToIgnore);

		TArray<AActor*> OutActors;

		bool bHit = UKismetSystemLibrary::SphereOverlapActors(
			this->GetWorld(),
			Location,
			Radius,
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

void UMagic_AttackSphere::OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Enemies.Empty();
	if(!OwningInstance) return;
	OwningInstance->GetOwningActor()->Destroy();
}
