// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Amber_project/Backpack/EquipmentComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Backpack_Equip.generated.h"
class UBackpack;
/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UBackpack_Equip : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;

	UFUNCTION(BlueprintCallable)
	void SetEquipWidget(FEquipComponent& InEquipment,UBackpack* InBackpack);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEquipComponent Equipment;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBackpack* Backpack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUse = false;
};
