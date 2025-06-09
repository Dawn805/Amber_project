// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimNotifyState.h"
#include "Magic_Buff_HP.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UMagic_Buff_HP : public UPaperZDAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) const override;
	virtual void OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float HP_Current = 20.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float HP_Another = 10.0f;
};
