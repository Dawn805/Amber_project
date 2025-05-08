// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputComponent.h"
#include "UserInterface/Settings.h"
#include "Amber_project/UserInterface/Component/KeySaveLibrary.h"
class AMainPaperZDCharacter;
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputMappingContext* InputMapping;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputAction* OpenMenuAction;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputAction* SwitchCharacterAction;

	UFUNCTION(BlueprintCallable)
	void OpenMenu(const struct FInputActionInstance& Instance);
	UFUNCTION(BlueprintCallable)
	void CloseMenu();
	
	UFUNCTION(BlueprintCallable)
	void OpenSettings();
	UFUNCTION(BlueprintCallable)
	void CloseSettings();

	UFUNCTION(BlueprintCallable)
	void SwitchCharacter();

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UUserWidget> MenuWidgetClass;
	UPROPERTY()
	UUserWidget* MenuWidgetInstance = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UUserWidget> SettingsWidgetClass;
	UPROPERTY()
	UUserWidget* SettingsWidgetInstance = nullptr;

public:
	UFUNCTION(BlueprintCallable)
	void InitKeySave();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Volume")
	USoundMix* SoundMix;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Volume")
	USoundClass* SoundClass_Master;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Volume")
	USoundClass* SoundClass_BGM;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Volume")
	USoundClass* SoundClass_Sound;

//更换角色
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AMainPaperZDCharacter> SwordsmanClass;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AMainPaperZDCharacter> WizardClass;

	UPROPERTY()
	AMainPaperZDCharacter* CharacterA;
	UPROPERTY()
	AMainPaperZDCharacter* CharacterB;
	UPROPERTY()
	AMainPaperZDCharacter* CurrentCharacter;
	UPROPERTY()
	AMainPaperZDCharacter* AnotherCharacter;

};
