// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimNotify.h"
#include "Notify_AttackBox.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UNotify_AttackBox : public UPaperZDAnimNotify
{
	GENERATED_BODY()

public:
	virtual void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance = nullptr) const override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float AttackDamage_Mult = 1.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector BoxExtent = FVector(10.0f, 10.0f, 10.0f);
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FColor BoxColor = FColor::Red;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName SocketName = "No";

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float BreakPoise = 10.0f;
};
