// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimNotifyState.h"
#include "Amber_project/Enemy/MainPaperZDEnemy.h"
#include "Magic_AttackSphere.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UMagic_AttackSphere : public UPaperZDAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) const override;
	virtual void OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const override;
	virtual void OnNotifyTick_Implementation(float DeltaTime, UPaperZDAnimInstance* OwningInstance) const override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	mutable TArray<AMainPaperZDEnemy*> Enemies;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName SocketName = "No";

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Radius = 10.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float AttackDamage_Mult = 1.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float BreakPoise = 20.0f;
};
