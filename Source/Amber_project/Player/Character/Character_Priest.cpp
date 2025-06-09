// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Priest.h"

#include "PaperZDAnimInstance.h"


// Sets default values
ACharacter_Priest::ACharacter_Priest()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACharacter_Priest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacter_Priest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacter_Priest::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACharacter_Priest::Attack_J(const struct FInputActionInstance& Instance)
{
	if (!AnimRight) return;
	if (StateComponent->MP < 0.0f) return;
	UPaperZDAnimInstance* PriestAnimInstance = this->GetAnimInstance();
	if (PriestAnimInstance && StateMachineName != "No" && AnimName_Attack_J != "No")
	{
		PriestAnimInstance->JumpToNode(AnimName_Attack_J,StateMachineName);
		StateComponent->MP -= 0.0f;
	}
}

void ACharacter_Priest::Attack_U(const struct FInputActionInstance& Instance)
{
	if (!AnimRight) return;
	if (StateComponent->MP < 10.0f) return;
	UPaperZDAnimInstance* PriestAnimInstance = this->GetAnimInstance();
	if (PriestAnimInstance && StateMachineName != "No" && AnimName_Attack_U != "No")
	{
		PriestAnimInstance->JumpToNode(AnimName_Attack_U,StateMachineName);
		StateComponent->MP -= 10.0f;
	}
}

void ACharacter_Priest::Attack_I(const struct FInputActionInstance& Instance)
{
	if (!AnimRight) return;
	UPaperZDAnimInstance* PriestAnimInstance = this->GetAnimInstance();
	if (PriestAnimInstance && StateMachineName != "No" && AnimName_Attack_I != "No")
	{
		PriestAnimInstance->JumpToNode(AnimName_Attack_I,StateMachineName);
	}
}