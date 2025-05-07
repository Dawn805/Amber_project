// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Enemy_SkillComponent.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FEnemySkill
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SkillName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxRange = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight = 1;
};


UCLASS()
class AMBER_PROJECT_API UEnemy_SkillComponent : public UObject
{
	GENERATED_BODY()
};
