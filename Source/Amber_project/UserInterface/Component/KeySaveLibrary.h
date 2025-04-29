// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Amber_project/SaveGame/KeySaveGame.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "KeySaveLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UKeySaveLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "KeySaveLibrary")
	static void CreateSave();

	UFUNCTION(BlueprintCallable, Category = "KeySaveLibrary")
	static UKeySaveGame* GetSave();

	UFUNCTION(BlueprintCallable, Category = "KeySaveLibrary")
	static TMap<int,FKey> GetStatKeyMap();

	UFUNCTION(BlueprintCallable, Category = "KeySaveLibrary")
	static void SetStatKeyMap(TMap<int,FKey>& InKeyMap);

	UFUNCTION(BlueprintCallable, Category = "KeySaveLibrary")
	static TMap<int, FKey> ResetStatKeyMap();

};
