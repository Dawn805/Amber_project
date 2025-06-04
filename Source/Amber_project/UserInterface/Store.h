// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Store_th.h"
#include "Amber_project/Backpack/BackpackComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "Store.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UStore : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FBackpackItems> StoreItems;

	UPROPERTY(meta=(BindWidget))
	UUniformGridPanel* GridPanel_Items;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UStore_th> StoreThClass;
};
