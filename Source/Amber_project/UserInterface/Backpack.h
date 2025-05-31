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

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

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

	//给物品添加描述
public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_Describe;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Item_Describe = "nullptr";
};
