// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Continue;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Settings;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_GotoMainMenu;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Exit;

public:
	UFUNCTION(BlueprintCallable)
	void Button_Continue_OnClicked();
	UFUNCTION(BlueprintCallable)
	void Button_Exit_OnClicked();


};
