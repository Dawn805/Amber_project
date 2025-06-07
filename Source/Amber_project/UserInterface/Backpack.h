// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Backpack_Equip.h"
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

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UEquipmentComponent* EquipmentComponent;

protected:
	virtual void NativeConstruct() override;

public:
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

	//在背包中给不同的角色使用物品
public:
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Character_A;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Character_B;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AMainPaperZDCharacter* CurrentCharacter = nullptr;

	UFUNCTION(BlueprintCallable)
	void SetCharacter_A();
	UFUNCTION(BlueprintCallable)
	void SetCharacter_B();

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_Character_Attributes;

	//装备界面
	UPROPERTY(meta=(bindWidget))
	UUniformGridPanel* GridPanel_Equipment;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UBackpack_Equip> BackpackEquipClass;

	//界面切换
	UPROPERTY(meta=(bindWidget))
	UWidgetSwitcher* PanelSwitcher;
	UPROPERTY(meta=(bindWidget))
	UCanvasPanel* Panel_Item;
	UPROPERTY(meta=(bindWidget))
	UCanvasPanel* Panel_Equipment;

	UPROPERTY(meta=(bindWidget))
	UButton* Button_Choose_Item;
	UPROPERTY(meta=(bindWidget))
	UButton* Button_Choose_Equipment;
	
	UFUNCTION(BlueprintCallable)
	void ChoosePanel_Item();
	UFUNCTION(BlueprintCallable)
	void ChoosePanel_Equipment();

	//装备槽的显示
	UPROPERTY(meta=(bindWidget))
	UImage* Image_Slot0;
	UPROPERTY(meta=(bindWidget))
	UImage* Image_Slot1;
	UPROPERTY(meta=(bindWidget))
	UImage* Image_Slot2;
	UPROPERTY(meta=(bindWidget))
	UImage* Image_Slot3;

	UPROPERTY(meta=(bindWidget))
	UButton* Button_Slot0;
	UPROPERTY(meta=(bindWidget))
	UButton* Button_Slot1;
	UPROPERTY(meta=(bindWidget))
	UButton* Button_Slot2;
	UPROPERTY(meta=(bindWidget))
	UButton* Button_Slot3;

	UFUNCTION(BlueprintCallable)
	void On_Button_Slot0_Clicked();
	UFUNCTION(BlueprintCallable)
	void On_Button_Slot1_Clicked();
	UFUNCTION(BlueprintCallable)
	void On_Button_Slot2_Clicked();
	UFUNCTION(BlueprintCallable)
	void On_Button_Slot3_Clicked();

	//装备的卸下
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Remove0;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Remove1;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Remove2;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Remove3;

	UFUNCTION(BlueprintCallable)
	void On_Button_Remove0_Clicked();
	UFUNCTION(BlueprintCallable)
	void On_Button_Remove1_Clicked();
	UFUNCTION(BlueprintCallable)
	void On_Button_Remove2_Clicked();
	UFUNCTION(BlueprintCallable)
	void On_Button_Remove3_Clicked();
};
