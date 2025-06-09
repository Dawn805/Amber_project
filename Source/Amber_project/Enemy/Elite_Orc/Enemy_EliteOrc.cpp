// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_EliteOrc.h"


// Sets default values
AEnemy_EliteOrc::AEnemy_EliteOrc()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MaxHP = 300.0f;
	HP = 300.0f;
	Damage = 10.0f;
	Defense = 3.0f;
	Poise = 30.0f;
	MaxPoise = 30.0f;

	FEnemySkill Attack_01;
	Attack_01.SkillName = "Attack_01";
	Attack_01.MaxRange = 100.0f;
	Attack_01.Weight = 10;
	FEnemySkill Attack_02;
	Attack_02.SkillName = "Attack_02";
	Attack_02.MaxRange = 100.0f;
	Attack_02.Weight = 10;
	FEnemySkill Attack_03;
	Attack_03.SkillName = "Attack_03";
	Attack_03.MaxRange = 100.0f;
	Attack_03.Weight = 10;

	Enemy_Skills.Add(Attack_01);
	Enemy_Skills.Add(Attack_02);
	Enemy_Skills.Add(Attack_03);
}

// Called when the game starts or when spawned
void AEnemy_EliteOrc::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy_EliteOrc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemy_EliteOrc::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

