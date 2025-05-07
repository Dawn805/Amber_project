// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPaperZDEnemy.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "PaperFlipbookComponent.h"
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
}

// Called to bind functionality to input
void AMainPaperZDEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMainPaperZDEnemy::AITree_Begin()
{
	AAIController* EnemyAIController = Cast<AAIController>(GetController());
	if (!EnemyAIController) return;

	EnemyAIController->GetBrainComponent()->RestartLogic();
}

void AMainPaperZDEnemy::AITree_End()
{
	AAIController* EnemyAIController = Cast<AAIController>(GetController());
	if (!EnemyAIController) return;

	EnemyAIController->GetBrainComponent()->StopLogic("Death");
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

