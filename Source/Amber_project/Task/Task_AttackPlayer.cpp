// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_AttackPlayer.h"

#include "AIController.h"
#include "PaperZDAnimInstance.h"
#include "Amber_project/Enemy/Enemy_SkillComponent.h"
#include "Amber_project/Enemy/MainPaperZDEnemy.h"
#include "Amber_project/Player/MainPaperZDCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

EBTNodeResult::Type UTask_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	AMainPaperZDEnemy* AIEnemy = Cast<AMainPaperZDEnemy>(AIController->GetCharacter());
	if (!AIEnemy) return EBTNodeResult::Failed;

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComponent) return EBTNodeResult::Failed;

	AMainPaperZDCharacter* PlayerCharacter = Cast<AMainPaperZDCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!PlayerCharacter) return EBTNodeResult::Failed;

	float Distance = (PlayerCharacter->GetActorLocation() - AIEnemy->GetActorLocation()).Size();
	if (FMath::Abs(Distance) > MaxLocation)
	{
		return EBTNodeResult::Failed;
	}
	
	FEnemySkill SelectedSkill = AIEnemy->ChooseSkill();
	if (SelectedSkill.SkillName.IsNone())
	{
		return EBTNodeResult::Failed;
	}

	if (AIEnemy->AnimRight == false) return EBTNodeResult::Failed;

	AIEnemy->GetAnimInstance()->JumpToNode(SelectedSkill.SkillName,StateMachineName);

	UKismetSystemLibrary::PrintString(this,"this");
	
	return EBTNodeResult::Succeeded;
}


