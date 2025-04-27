// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Amber_project/Player/MainPaperZDCharacter.h"
#include "Character_Swordsman.generated.h"

UCLASS()
class AMBER_PROJECT_API ACharacter_Swordsman : public AMainPaperZDCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_Swordsman();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void Attack_J(const struct FInputActionInstance& Instance) override;
	virtual void Attack_U(const struct FInputActionInstance& Instance) override;
	virtual void Attack_I(const struct FInputActionInstance& Instance) override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AnimName")
	FName AnimName_Attack_J_1 = "No";
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AnimName")
	FName AnimName_Attack_J_2 = "No";
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AnimName")
	FName AnimName_Attack_J_3 = "No";
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AnimName")
	FName AnimName_Attack_U = "No";
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AnimName")
	FName AnimName_Attack_I = "No";

public:
	UPROPERTY()
	TArray<bool> J_Keys;

public:
	UPROPERTY()
	FTimerHandle TimerHandle_J2_3;
	UPROPERTY()
	FTimerHandle TimerHandle_J1_2;
	UFUNCTION()
	void Attack_J2_3();
	UFUNCTION()
	void Attack_J1_2();
};
