// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPaperZDEnemy.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimInstance.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AMainPaperZDEnemy::AMainPaperZDEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0,1,0));
}

// Called when the game starts or when spawned
void AMainPaperZDEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainPaperZDEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Poise <= 0 && HP > 0)
	{
		UPaperZDAnimInstance* ZDAnimInstance = this->GetAnimInstance();
		if (ZDAnimInstance)
		{
			if (StateMachineName != "No" && AnimNodeName_Hurt != "No" && AnimRight)
			{
				ZDAnimInstance->JumpToNode(AnimNodeName_Hurt,StateMachineName);
			}
		}
	}

	if (HP <= 0)
	{
		UPaperZDAnimInstance* ZDAnimInstance = this->GetAnimInstance();
		if (ZDAnimInstance)
		{
			if (StateMachineName != "No" && AnimNodeName_Death != "No" && AnimRight)
			{
				ZDAnimInstance->JumpToNode(AnimNodeName_Death,StateMachineName);
			}
		}
	}
}

// Called to bind functionality to input
void AMainPaperZDEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMainPaperZDEnemy::AITree_Begin()
{
	// if (AAIController* EnemyAIController = Cast<AAIController>(GetController()))
	// {
	// 	if (UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(EnemyAIController->BrainComponent))
	// 	{
	// 		BTComp->StartTree(*BehaviorTreeAsset);
	// 	}
	// }
	AAIController* FAIController = Cast<AAIController>(GetController());
	if (FAIController && FAIController->GetBrainComponent())
	{
		FAIController->GetBrainComponent()->RestartLogic();
	}
}

void AMainPaperZDEnemy::AITree_End()
{
	// if (AAIController* EnemyAIController = Cast<AAIController>(GetController()))
	// {
	// 	if (UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(EnemyAIController->BrainComponent))
	// 	{
	// 		BTComp->StopTree(EBTStopMode::Forced);
	// 	}
	// }
	AAIController* FAIController = Cast<AAIController>(GetController());
	if (FAIController && FAIController->GetBrainComponent())
	{
		FAIController->GetBrainComponent()->StopLogic("Died");
	}
}

FEnemySkill AMainPaperZDEnemy::ChooseSkill()
{
	TArray<FEnemySkill>& SkillPool = Enemy_Skills;
	if (SkillPool.Num() == 0) return FEnemySkill();

	TArray<int> Weights;
	int TotalWeight = 0;

	for (int i = 0 ; i < SkillPool.Num() ; i++)
	{
		int Sub_Weight;
		if (SkillPool[i].SkillName == LastSkill)
		{
			Sub_Weight = SkillPool[i].Weight/2;
		}else
		{
			Sub_Weight = SkillPool[i].Weight;
		}

		Weights.Add(Sub_Weight);
		TotalWeight += Sub_Weight;
	}

	int RandomValue = FMath::RandRange(1, TotalWeight);
	int Accumulated = 0;

	for (int i = 0 ; i < SkillPool.Num() ; i++)
	{
		Accumulated += Weights[i];
		if (RandomValue <= Accumulated)
		{
			LastSkill = SkillPool[i].SkillName;
			return SkillPool[i];
		}
	}
	
	return SkillPool[0];
}

