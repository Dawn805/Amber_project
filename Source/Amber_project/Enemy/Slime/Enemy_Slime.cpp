// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Slime.h"

#include "PaperZDAnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AEnemy_Slime::AEnemy_Slime()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MaxHP = 30.0f;
	HP = 30.0f;
	Damage = 10.0f;
	Defense = 0.0f;
	Poise = 10.0f;
	MaxPoise = 10.0f;

	FEnemySkill Attack_01;
	Attack_01.SkillName = "Attack_01";
	Attack_01.MaxRange = 100.0f;
	Attack_01.Weight = 5;
	FEnemySkill Attack_02;
	Attack_02.SkillName = "Attack_02";
	Attack_02.MaxRange = 100.0f;
	Attack_02.Weight = 5;

	Enemy_Skills.Add(Attack_01);
	Enemy_Skills.Add(Attack_02);
}

// Called when the game starts or when spawned
void AEnemy_Slime::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy_Slime::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemy_Slime::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


