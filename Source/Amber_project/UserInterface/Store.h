// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
class UStore_th;
#include "Amber_project/Backpack/BackpackComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Store.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FStoreItems
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int ItemCount = 1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* ItemIcon;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int Cost = 0;
};


UCLASS()
class AMBER_PROJECT_API UStore : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FStoreItems> StoreItems;

	UPROPERTY(meta=(BindWidget))
	UUniformGridPanel* GridPanel_Items;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UStore_th> StoreThClass;

	UFUNCTION(BlueprintCallable)
	void RefreshItem();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString Item_Describe = "nullptr";

	UPROPERTY(meta=(bindWidget))
	UTextBlock* Text_Describe;

	UPROPERTY(meta=(bindWidget))
	UTextBlock* Text_Money;



	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* ItemIcon_1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* ItemIcon_2;
};
