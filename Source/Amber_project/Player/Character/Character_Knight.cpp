// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Knight.h"

#include "PaperZDAnimInstance.h"

// Sets default values
ACharacter_Knight::ACharacter_Knight()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACharacter_Knight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacter_Knight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacter_Knight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACharacter_Knight::Attack_J(const struct FInputActionInstance& Instance)
{
	if (!AnimRight) return;
	if (StateComponent->MP < 0.0f) return;
	UPaperZDAnimInstance* KnightAnimInstance = this->GetAnimInstance();
	if (KnightAnimInstance && StateMachineName != "No" && AnimName_Attack_J != "No")
	{
		KnightAnimInstance->JumpToNode(AnimName_Attack_J,StateMachineName);
		StateComponent->MP -= 0.0f;
	}
}

void ACharacter_Knight::Attack_U(const struct FInputActionInstance& Instance)
{
	if (!AnimRight) return;
	if (StateComponent->MP < 10.0f) return;
	UPaperZDAnimInstance* KnightAnimInstance = this->GetAnimInstance();
	if (KnightAnimInstance && StateMachineName != "No" && AnimName_Attack_U != "No")
	{
		KnightAnimInstance->JumpToNode(AnimName_Attack_U,StateMachineName);
		StateComponent->MP -= 10.0f;
	}
}

void ACharacter_Knight::Attack_I(const struct FInputActionInstance& Instance)
{
	if (!AnimRight) return;
	if (StateComponent->MP < 20.0f) return;
	UPaperZDAnimInstance* KnightAnimInstance = this->GetAnimInstance();
	if (KnightAnimInstance && StateMachineName != "No" && AnimName_Attack_I != "No")
	{
		KnightAnimInstance->JumpToNode(AnimName_Attack_I,StateMachineName);
		StateComponent->MP -= 20.0f;
	}
}
