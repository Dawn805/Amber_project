// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "KeysChangeManager.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AMBER_PROJECT_API UKeysChangeManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "KeysChangeManager")
	void Initialize(class UEnhancedInputLocalPlayerSubsystem* Subsystem);
	UFUNCTION(BlueprintCallable, Category = "KeysChangeManager")
	void SaveKeyMapping();
	UFUNCTION(BlueprintCallable, Category = "KeysChangeManager")
	TMap<int,FKey> GetKeyMap();
	UFUNCTION(BlueprintCallable, Category = "KeysChangeManager")
	void SetKeyMap(int KeyID,FKey NewKey);
	UFUNCTION(BlueprintCallable, Category = "KeysChangeManager")
	void ResetKeyMap();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UEnhancedInputLocalPlayerSubsystem> InputSubsystem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UKeySaveGame> KeySaveObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SaveSlotName = "KeySaveSlot";
	UFUNCTION(BlueprintCallable, Category = "KeysChangeManager")
	void CreateOrLoadSave();
};
