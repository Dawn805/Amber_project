// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Wizard.h"

#include "PaperZDAnimInstance.h"


// Sets default values
ACharacter_Wizard::ACharacter_Wizard()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (StateComponent)
	{
		StateComponent->HP_Max = 80.0f;
		StateComponent->HP = StateComponent->HP_Max;
		StateComponent->MP_Max = 100.0f;
		StateComponent->MP = StateComponent->MP_Max;
		StateComponent->Damage = 15.0f;
		StateComponent->Defense = 3.0f;
	}
}

// Called when the game starts or when spawned
void ACharacter_Wizard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacter_Wizard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacter_Wizard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACharacter_Wizard::Attack_J(const struct FInputActionInstance& Instance)
{
	if (!AnimRight) return;
	if (StateComponent->MP < 5.0f) return;
	UPaperZDAnimInstance* WizardAnimInstance = this->GetAnimInstance();
	if (WizardAnimInstance && StateMachineName != "No" && AnimName_Attack_J != "No")
	{
		WizardAnimInstance->JumpToNode(AnimName_Attack_J,StateMachineName);
		StateComponent->MP -= 5.0f;
	}
}

void ACharacter_Wizard::Attack_U(const struct FInputActionInstance& Instance)
{
	if (!AnimRight) return;
	if (StateComponent->MP < 15.0f) return;
	UPaperZDAnimInstance* WizardAnimInstance = this->GetAnimInstance();
	if (WizardAnimInstance && StateMachineName != "No" && AnimName_Attack_U != "No")
	{
		WizardAnimInstance->JumpToNode(AnimName_Attack_U,StateMachineName);
		StateComponent->MP -= 15.0f;
	}
}

void ACharacter_Wizard::Attack_I(const struct FInputActionInstance& Instance)
{
	if (!AnimRight) return;
	UPaperZDAnimInstance* WizardAnimInstance = this->GetAnimInstance();
	if (WizardAnimInstance && StateMachineName != "No" && AnimName_Attack_I != "No")
	{
		WizardAnimInstance->JumpToNode(AnimName_Attack_I,StateMachineName);
	}
}

