// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Volume")
	USoundMix* SoundMix;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Volume")
	USoundClass* SoundClass_Master;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Volume")
	USoundClass* SoundClass_BGM;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Volume")
	USoundClass* SoundClass_Sound;

	UFUNCTION()
	void OnPostLoadMap(UWorld* LoadedWorld);
};
