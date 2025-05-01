// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "KeySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UKeySaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UKeySaveGame();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int,FKey> DefaultKeyMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int,FKey> CurrentKeyMap;
	
public:
	UFUNCTION(BlueprintCallable)
	TMap<int,FKey> GetKeyMap();

	UFUNCTION(BlueprintCallable)
	void SetKeyMap(const TMap<int,FKey>& NewKeyMap);

	UFUNCTION(BlueprintCallable)
	TMap<int,FKey> ResetKeyMap();
};
