// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Amber_project/Backpack/BackpackComponent.h"
#include "GameFramework/SaveGame.h"
#include "GameSave.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UGameSave : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector PlayerLocation;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FRotator PlayerRotation;

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FBackpackItems> SaveItems;



	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintCallable)
	void LoadGame();
};

