// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
class UBackpack;
#include "Amber_project/Backpack/BackpackComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Backpack_th.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UBackpack_th : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemCount;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void SetItemWidget(FBackpackItems& Item,UBackpackComponent* InBackpackComponent,UBackpack* InBackpack);

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBackpackItems Item_0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBackpackComponent* BackpackComponent_0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBackpack* Backpack_0;
	
	//点击使用
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Background;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Use;

	UFUNCTION(BlueprintCallable)
	void On_ButtonBackground_Clicked();
	UFUNCTION(BlueprintCallable)
	void On_ButtonUse_Clicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUse = false;

	//使用按钮将在显示3秒后关闭
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float ThreeTime = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bButton_Show = false;
};
