// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Amber_project/Enemy/MainPaperZDEnemy.h"
#include "Enemy_GreatswordSkeleton.generated.h"

UCLASS()
class AMBER_PROJECT_API AEnemy_GreatswordSkeleton : public AMainPaperZDEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy_GreatswordSkeleton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
