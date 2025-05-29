// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Backpack_th.h"
#include "Amber_project/MainPlayerController.h"
#include "Amber_project/Backpack/BackpackComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "Backpack.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UBackpack : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBackpackComponent* BackpackComponent;

	UFUNCTION(BlueprintCallable)
	void SetBackpackComponent(AMainPlayerController* Controller);

	UPROPERTY(meta=(BindWidget))
	UUniformGridPanel* GridPanel;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UBackpack_th> BackpackThClass;

	UFUNCTION(BlueprintCallable)
	void RefreshBackpack();

	//显示当前角色
	UPROPERTY(meta=(BindWidget))
	UImage* Character_Image;
};
