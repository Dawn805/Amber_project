// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Store.h"
#include "Amber_project/Backpack/BackpackComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Store_th.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UStore_th : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;

	UFUNCTION(BlueprintCallable)
	void SetItemWidget(FStoreItems Item,UStore* InStore);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStoreItems Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStore* Store;

	UPROPERTY(meta = (BindWidget))
	UButton* ItemToDescribe;

	UFUNCTION(BlueprintCallable)
	void ButtonOnClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUse = false;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Buy;
	
	UFUNCTION(BlueprintCallable)
	void Button_BuyOnClicked();

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Item_Cost;
};
