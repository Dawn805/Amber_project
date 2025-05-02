// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Swordsman.h"

#include "PaperZDAnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"


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
	
	J_Keys.Init(false,2);
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
	UPaperZDAnimInstance* FAnimInstance = this->GetAnimInstance();
	if (!FAnimInstance) return;
	if (StateMachineName == "No" || AnimName_Attack_J_1 == "No" || AnimName_Attack_J_2 == "No" || AnimName_Attack_J_3 == "No") return;
	if (J_Keys[1] == true)
	{
		FAnimInstance->JumpToNode(AnimName_Attack_J_3,StateMachineName);
		J_Keys[0] = false;
		J_Keys[1] = false;
		GetWorldTimerManager().ClearTimer(TimerHandle_J1_2);
		GetWorldTimerManager().ClearTimer(TimerHandle_J2_3);
		return;
	}
	if (J_Keys[0] == true)
	{
		FAnimInstance->JumpToNode(AnimName_Attack_J_2,StateMachineName);
		J_Keys[1] = true;
		J_Keys[0] = false;
		GetWorldTimerManager().ClearTimer(TimerHandle_J1_2);
		GetWorldTimerManager().ClearTimer(TimerHandle_J2_3);
		GetWorldTimerManager().SetTimer(TimerHandle_J2_3,this,&ACharacter_Swordsman::Attack_J2_3,2.0f,false);
		return;
	}
	if (J_Keys[0] == false && J_Keys[1] == false)
	{
		FAnimInstance->JumpToNode(AnimName_Attack_J_1,StateMachineName);
		J_Keys[0] = true;
		GetWorldTimerManager().ClearTimer(TimerHandle_J1_2);
		GetWorldTimerManager().ClearTimer(TimerHandle_J2_3);
		GetWorldTimerManager().SetTimer(TimerHandle_J1_2,this,&ACharacter_Swordsman::Attack_J1_2,1.0f,false);
		return;
	}
}
void ACharacter_Swordsman::Attack_J2_3()
{
	J_Keys[1] = false;
}
void ACharacter_Swordsman::Attack_J1_2()
{
	J_Keys[0] = false;
}


void ACharacter_Swordsman::Attack_U(const FInputActionInstance& Instance)
{
	if (StateComponent->MP < 8.0f) return;
	UPaperZDAnimInstance* FAnimInstance = this->GetAnimInstance();
	if (FAnimInstance && AnimName_Attack_U != "No" && StateMachineName != "No")
	{
		FAnimInstance->JumpToNode(AnimName_Attack_U,StateMachineName);
		StateComponent->MP = StateComponent->MP - 8.0f;
	}
}


void ACharacter_Swordsman::Attack_I(const FInputActionInstance& Instance)
{
	if (StateComponent->MP < 10.0f) return;
	UPaperZDAnimInstance* FAnimInstance = this->GetAnimInstance();
	if (FAnimInstance && AnimName_Attack_I!= "No" && StateMachineName != "No")
	{
		FAnimInstance->JumpToNode(AnimName_Attack_I,StateMachineName);
		StateComponent->MP = StateComponent->MP - 10.0f;
	}
}

