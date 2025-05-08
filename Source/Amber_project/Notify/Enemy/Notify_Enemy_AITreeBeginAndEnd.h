// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimNotifyState.h"
#include "Notify_Enemy_AITreeBeginAndEnd.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UNotify_Enemy_AITreeBeginAndEnd : public UPaperZDAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) const override;
	virtual void OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const override;
};
