// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Amber_project/Player/MainPaperZDCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "SelectCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API USelectCharacter : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Sword;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Wizard;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Priest;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_OnConfirmSelection;

	UPROPERTY()
	TArray<TSubclassOf<AMainPaperZDCharacter>> SelectedClasses;

	//剑士
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMainPaperZDCharacter> SwordsmanClass;
	//法师
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMainPaperZDCharacter> WizardClass;
	//牧师
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AMainPaperZDCharacter> PriestClass;

	UFUNCTION(BlueprintCallable)
	void OnSelectSwordsman();
	UFUNCTION(BlueprintCallable)
	void OnSelectWizard();
	UFUNCTION(BlueprintCallable)
	void OnSelectPriest();

	UFUNCTION(BlueprintCallable)
	void OnConfirmSelection();
};
