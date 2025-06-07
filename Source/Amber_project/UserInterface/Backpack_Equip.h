// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Amber_project/Backpack/EquipmentComponent.h"
#include "Amber_project/Player/MainPaperZDCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Messaging/Popup.h"
#include "Backpack_Equip.generated.h"
class UBackpack;
/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UBackpack_Equip : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;

	UFUNCTION(BlueprintCallable)
	void SetEquipWidget(FEquipComponent& InEquipment,UBackpack* InBackpack,int InNumber,AMainPaperZDCharacter* InCharacter);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEquipComponent Equipment;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBackpack* Backpack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUse = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMainPaperZDCharacter* CurrentCharacter;

	//背包物品编号，出售的时候用来RemoveAt
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Number;

	//按钮，用来显示下面两个按钮
	UPROPERTY(meta=(bindWidget))
	UButton* Button_Show;

	UFUNCTION(BlueprintCallable)
	void Button_Show_OnClicked();
	
	//两个按钮，出售和使用
	UPROPERTY(meta=(bindWidget))
	UButton* Button_Sale;
	UPROPERTY(meta=(bindWidget))
	UButton* Button_Use;

	UFUNCTION(BlueprintCallable)
	void Button_Sale_OnClicked();
	UFUNCTION(BlueprintCallable)
	void Button_Use_OnClicked();

	//还是三秒钟就隐藏按钮，在NativeTick里面写
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ThreeSeconds = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bButtonShow = false;

	//写两个弹窗，一个是装备不适配，一个是装备槽有装备
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPopup> PopupClass_1;
	UPROPERTY()
	UPopup* PopupInstance_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPopup> PopupClass_2;
	UPROPERTY()
	UPopup* PopupInstance_2;
};
