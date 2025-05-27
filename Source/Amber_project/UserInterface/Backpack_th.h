// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	UFUNCTION(BlueprintCallable)
	void SetItemWidget(FBackpackItems& Item,UBackpackComponent* InBackpackComponent,UBackpack* InBackpack);

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBackpackItems Item_0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBackpackComponent* BackpackComponent_0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBackpack* Backpack_0;
};
