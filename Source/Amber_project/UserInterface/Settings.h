// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Settings.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API USettings : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	UButton* Button_KeysChange;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Sound;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_ComeBack;

public:
	UFUNCTION(BlueprintCallable)
	void Button_KeysChange_OnClicked();
	UFUNCTION(BlueprintCallable)
	void Button_Sound_OnClicked();
	UFUNCTION(BlueprintCallable)
	void Button_Come_Back_OnClicked();
};
