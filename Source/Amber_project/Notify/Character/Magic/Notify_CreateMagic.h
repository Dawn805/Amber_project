// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimNotify.h"

#include "Notify_CreateMagic.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UNotify_CreateMagic : public UPaperZDAnimNotify
{
	GENERATED_BODY()
//从角色身上从左到右
public:
	virtual void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance = nullptr) const override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Location = 1.0f;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AActor> MagicClass;
};
