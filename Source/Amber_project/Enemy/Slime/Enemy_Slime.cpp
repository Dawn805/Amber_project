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
	Damage = 2.0f;
	Defense = 0.0f;
	Poise = 10.0f;
	MaxPoise = 10.0f;
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

	FString Text = TEXT("当前HP：") + FString::SanitizeFloat(HP);
	UKismetSystemLibrary::PrintString(this, Text);

	if (Poise <= 0 && HP > 0)
	{
		UPaperZDAnimInstance* ZDAnimInstance = this->GetAnimInstance();
		if (ZDAnimInstance)
		{
			if (StateMachineName != "No" && AnimNodeName_Hurt != "No" && AnimRight)
			{
				ZDAnimInstance->JumpToNode(AnimNodeName_Hurt,StateMachineName);
			}
		}
	}

	if (HP <= 0)
	{
		UPaperZDAnimInstance* ZDAnimInstance = this->GetAnimInstance();
		if (ZDAnimInstance)
		{
			if (StateMachineName != "No" && AnimNodeName_Death != "No" && AnimRight)
			{
				ZDAnimInstance->JumpToNode(AnimNodeName_Death,StateMachineName);
			}
		}
	}
}

// Called to bind functionality to input
void AEnemy_Slime::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

