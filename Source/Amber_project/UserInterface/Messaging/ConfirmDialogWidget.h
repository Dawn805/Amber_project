// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ConfirmDialogWidget.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UConfirmDialogWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void Init(UObject* WorldContext,FSimpleDelegate Yes,FSimpleDelegate No,float whentime);
	

	UFUNCTION(BlueprintCallable)
	void OnYesClicked();
	UFUNCTION(BlueprintCallable)
	void OnNoClicked();

public:
	FSimpleDelegate OnYes;
	FSimpleDelegate OnNo;

public:
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Yes;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_No;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RemainingTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OneTime = 0.0f;
	
	UFUNCTION(BlueprintCallable)
	void UpdateCountdown();
};
