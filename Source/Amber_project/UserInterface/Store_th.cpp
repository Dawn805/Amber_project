// Fill out your copyright notice in the Description page of Project Settings.


#include "Store_th.h"
#include "Store.h"
#include "Amber_project/MainPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UStore_th::NativeConstruct()
{
	Super::NativeConstruct();
	ItemToDescribe->OnClicked.AddDynamic(this,&UStore_th::ButtonOnClicked);
	Button_Buy->OnClicked.AddDynamic(this,&UStore_th::Button_BuyOnClicked);
	
	if (!bUse)
	{
		Button_Buy->SetVisibility(ESlateVisibility::Hidden);
	}

	Item_Cost->SetText(FText::FromString(FString::Printf(TEXT("%d金币"), Item.Cost)));
}

void UStore_th::SetItemWidget(FStoreItems InItem,UStore* InStore)
{
	FSlateBrush Brush;
	Brush.SetResourceObject(InItem.ItemIcon);
	ItemIcon->SetBrush(Brush);

	Item = InItem;

	Store = InStore;
}

void UStore_th::ButtonOnClicked()
{
	if (!bUse) return;
	Store->Item_Describe = (Item.ItemName).ToString();
}

void UStore_th::Button_BuyOnClicked()
{
	AMainPlayerController* PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	if (PlayerController)
	{
		if (PlayerController->Money >= Item.Cost)
		{
			PlayerController->BackpackComponent->AddItem({Item.ItemName,1,Item.ItemIcon});
			PlayerController->Money -= Item.Cost;
		}
	}

	Store->Item_Describe = (Item.ItemName).ToString();
	
}