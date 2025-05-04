// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "MainPaperZDEnemy.generated.h"

UCLASS()
class AMBER_PROJECT_API AMainPaperZDEnemy : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainPaperZDEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HP = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Defense = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool AnimRight = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxPoise = 30.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Poise = 30.0f;
};
