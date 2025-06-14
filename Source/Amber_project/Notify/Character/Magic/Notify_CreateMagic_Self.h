// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimNotify.h"
#include "Notify_CreateMagic_Self.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UNotify_CreateMagic_Self : public UPaperZDAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance = nullptr) const override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AActor> MagicClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName SocketName = "No";

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bMovement = false;
};
