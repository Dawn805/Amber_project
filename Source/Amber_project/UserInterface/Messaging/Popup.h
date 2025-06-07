// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Popup.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UPopup : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Yes;

	UFUNCTION(BlueprintCallable)
	void On_Button_Yes_Clicked();
};
