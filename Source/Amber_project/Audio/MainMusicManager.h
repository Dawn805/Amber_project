// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "MainMusicManager.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UMainMusicManager : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual TStatId GetStatId() const override;
	virtual void PostInitialize() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Volume")
	USoundMix* SoundMix;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Volume")
	USoundClass* SoundClass_Master;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Volume")
	USoundClass* SoundClass_BGM;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Volume")
	USoundClass* SoundClass_Sound;

	UFUNCTION(BlueprintCallable)
	void ApplyVolume();


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USoundBase* CurrentSound = nullptr;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAudioComponent* AudioComponent = nullptr;

	UFUNCTION(BlueprintCallable)
	void PlaySound(USoundBase* Sound,float whenout,float whenin,float VolumeValue);
	
};
