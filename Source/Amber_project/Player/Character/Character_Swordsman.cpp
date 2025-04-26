// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Swordsman.h"


// Sets default values
ACharacter_Swordsman::ACharacter_Swordsman()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (StateComponent)
	{
		StateComponent->HP_Max = 100.0f;
		StateComponent->HP = StateComponent->HP_Max;
		StateComponent->MP_Max = 70.0f;
		StateComponent->MP = StateComponent->MP_Max;
		StateComponent->Damage = 10.0f;
		StateComponent->Defense = 5.0f;
	}
}

// Called when the game starts or when spawned
void ACharacter_Swordsman::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacter_Swordsman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacter_Swordsman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void ACharacter_Swordsman::Attack_J(const FInputActionInstance& Instance)
{
	
}

void ACharacter_Swordsman::Attack_U(const FInputActionInstance& Instance)
{
	
}

void ACharacter_Swordsman::Attack_I(const FInputActionInstance& Instance)
{
	
}

