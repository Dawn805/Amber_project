// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimNotify.h"
#include "Notify_Enemy_AttackBox.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UNotify_Enemy_AttackBox : public UPaperZDAnimNotify
{
	GENERATED_BODY()

public:
	virtual void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance = nullptr) const override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SocketName = "No";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector BoxExtent = {10,10,10};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackDamage_Mult = 1.0f;
};
