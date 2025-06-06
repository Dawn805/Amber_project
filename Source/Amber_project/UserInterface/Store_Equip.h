// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Amber_project/Backpack/EquipmentComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Store_Equip.generated.h"

class UStore;
/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UStore_Equip : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;

	UFUNCTION(BlueprintCallable)
	void SetEquipWidget(FEquipComponent Item,UStore* InStore);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUse = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEquipComponent Equip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStore* Store;

	UPROPERTY(meta=(bindWidget))
	UButton* Button_Buy;

	UPROPERTY(meta=(bindWidget))
	UTextBlock* Text_Cost;

	UFUNCTION(BlueprintCallable)
	void AddEquipToBackpack();

	UPROPERTY(meta=(bindWidget))
	UButton* Button_EquipToDescribe;

	UFUNCTION(BlueprintCallable)
	void Button_EquipToDescribe_OnClicked();
};
