// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimNotifyState.h"
#include "Notify_Character_NoMove.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UNotify_Character_NoMove : public UPaperZDAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) const override;
	virtual void OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float BeginSpeed = 50.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float EndSpeed = 200.0f;
};
