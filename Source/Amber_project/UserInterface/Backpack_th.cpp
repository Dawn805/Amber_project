// Fill out your copyright notice in the Description page of Project Settings.


#include "Backpack_th.h"

#include "Backpack.h"

void UBackpack_th::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Background->OnClicked.AddDynamic(this,&UBackpack_th::On_ButtonBackground_Clicked);
	Button_Use->OnClicked.AddDynamic(this,&UBackpack_th::On_ButtonUse_Clicked);
	Button_Use->SetVisibility(ESlateVisibility::Hidden);
}

void UBackpack_th::SetItemWidget(FBackpackItems& Item, UBackpackComponent* InBackpackComponent, UBackpack* InBackpack)
{
	FSlateBrush Brush;
	Brush.SetResourceObject(Item.ItemIcon);
	ItemIcon->SetBrush(Brush);

	ItemCount->SetText(FText::AsNumber(Item.ItemCount));

	Item_0 = Item;
	BackpackComponent_0 = InBackpackComponent;
	Backpack_0 = InBackpack;
}

void UBackpack_th::On_ButtonBackground_Clicked()
{
	if (bUse)
	{
		Button_Use->SetVisibility(ESlateVisibility::Visible);
	}
	bButton_Show = true;
	
	//将物品信息传入Backpack
	Backpack_0->Item_Describe = Item_0.ItemName;
}

void UBackpack_th::On_ButtonUse_Clicked()
{
	BackpackComponent_0->UseItem(Item_0);
	Backpack_0->RefreshBackpack();
}

void UBackpack_th::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (bButton_Show)
	{
		ThreeTime = ThreeTime+InDeltaTime;
	}
	if (ThreeTime > 3.0f)
	{
		bButton_Show = false;
		ThreeTime = 0.0f;
		Button_Use->SetVisibility(ESlateVisibility::Hidden);
	}
}
