// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VolumeSave.generated.h"

/**
 * 
 */
UCLASS(Config = VolumeSave,DefaultConfig,meta = (DisplayName = "Volume Save"))
class AMBER_PROJECT_API UVolumeSave : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere,BlueprintReadWrite,Category="Volume Save")
	float MasterVolumeValue = 1.0f;
	UPROPERTY(Config, EditAnywhere,BlueprintReadWrite,Category="Volume Save")
	float BGMVolumeValue = 1.0f;
	UPROPERTY(Config,EditAnywhere,BlueprintReadWrite,Category="Volume Save")
	float SoundVolumeValue = 1.0f;
};
