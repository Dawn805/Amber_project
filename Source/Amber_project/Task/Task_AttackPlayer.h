// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_AttackPlayer.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UTask_AttackPlayer : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName StateMachineName = "No";

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxLocation = 50.0f;
};
