// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimNotify.h"
#include "Amber_project/Player/Character/Magic/Wizard_Attack_2.h"
#include "Notify_CreateMagic.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UNotify_CreateMagic : public UPaperZDAnimNotify
{
	GENERATED_BODY()

public:
	virtual void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance = nullptr) const override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Location = 1.0f;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Magic")
	TSubclassOf<AWizard_Attack_2> MagicClass;
};
