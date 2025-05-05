// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_ChasePlayer.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class AMBER_PROJECT_API UTask_ChasePlayer : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UTask_ChasePlayer();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
