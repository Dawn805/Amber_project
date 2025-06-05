// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputComponent.h"
#include "UserInterface/Settings.h"
#include "Amber_project/UserInterface/Component/KeySaveLibrary.h"
#include "Backpack/BackpackComponent.h"
#include "UserInterface/PlayerStateWidget.h"
#include "UserInterface/Store.h"
class UBackpack;
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

public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

public:
	AMainPlayerController();
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputMappingContext* InputMapping;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputAction* OpenMenuAction;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputAction* SwitchCharacterAction;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputAction* OpenBackpackAction;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputAction* OpenStoreAction;

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

	UFUNCTION(BlueprintCallable)
	void OpenBackpack();
	UFUNCTION(BlueprintCallable)
	void CloseBackpack();

	UFUNCTION(BlueprintCallable)
	void OpenStore();

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UUserWidget> MenuWidgetClass;
	UPROPERTY()
	UUserWidget* MenuWidgetInstance = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UUserWidget> SettingsWidgetClass;
	UPROPERTY()
	UUserWidget* SettingsWidgetInstance = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UBackpack> BackpackWidgetClass;
	UPROPERTY()
	UBackpack* BackpackWidgetInstance = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UStore> StoreWidgetClass;
	UPROPERTY()
	UStore* StoreWidgetInstance = nullptr;

public:
	UFUNCTION(BlueprintCallable)
	void InitKeySave();

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

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UPlayerStateWidget> PlayerStateWidgetClass;
	UPROPERTY()
	UPlayerStateWidget* PlayerStateWidgetInstance;

	//背包
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBackpackComponent* BackpackComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* Image_Character_Swordsman;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* Image_Character_Wizard;

	//装备
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UEquipmentComponent* EquipmentComponent;

	//打开商店
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bOpenStore = false;

	//这是能用的钱
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int Money = 10000;
};
