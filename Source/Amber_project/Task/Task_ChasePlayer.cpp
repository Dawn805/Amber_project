// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_ChasePlayer.h"

#include "AIController.h"
#include "Amber_project/Enemy/MainPaperZDEnemy.h"
#include "Amber_project/Player/MainPaperZDCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UTask_ChasePlayer::UTask_ChasePlayer()
{
	NodeName = "Task_ChasePlayer";
}


EBTNodeResult::Type UTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	AMainPaperZDEnemy* AIEnemy = Cast<AMainPaperZDEnemy>(AIController->GetCharacter());
	if (!AIEnemy) return EBTNodeResult::Failed;

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComponent) return EBTNodeResult::Failed;

	AMainPaperZDCharacter* PlayerCharacter = Cast<AMainPaperZDCharacter>(BlackboardComponent->GetValueAsObject("PlayerCharacter"));;
	if (!PlayerCharacter) return EBTNodeResult::Failed;
	
	AIController->MoveToActor(PlayerCharacter);
	return EBTNodeResult::Succeeded;
}
