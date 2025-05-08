// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Amber_project/MainPlayerController.h"
#include "Amber_project/Player/MainPaperZDCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "PlayerStateWidget.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UPlayerStateWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(Transient)
	AMainPlayerController* PlayerController;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HPBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* MPBar;
};
