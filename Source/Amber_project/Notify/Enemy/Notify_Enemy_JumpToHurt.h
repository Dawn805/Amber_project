// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimNotifyState.h"
#include "Notify_Enemy_JumpToHurt.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UNotify_Enemy_JumpToHurt : public UPaperZDAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void OnNotifyTick_Implementation(float DeltaTime, UPaperZDAnimInstance* OwningInstance) const override;
};
