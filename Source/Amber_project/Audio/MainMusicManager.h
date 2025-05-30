// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "MainMusicManager.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FAudioBGM
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* BGM;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Priority = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FadeInTime = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FadeOutTime = 1.0f;
};



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
	void PlaySound(USoundBase* Sound,float whenout,float whenin);

	//现在来写音频的优先级，上面的可以不用看了，如果写出来了就用不上了
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FAudioBGM> BGMs;

	UFUNCTION(BlueprintCallable)
	void BGMs_Sort();

	//有新的BGM进入
	UFUNCTION(BlueprintCallable)
	void PlayNewBGM(FAudioBGM NewBGM);

	//删除老的BGM，比如你战斗结束了，战斗BGM就该删掉了
	UFUNCTION(BlueprintCallable)
	void DeleteOldBGM(FAudioBGM OldBGM);
};
