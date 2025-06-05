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

void UBackpack_th::SetItemWidget(FBackpackItems& Item, UBackpackComponent* InBackpackComponent, UBackpack* InBackpack,AMainPaperZDCharacter* InCharacter)
{
	FSlateBrush Brush;
	Brush.SetResourceObject(Item.ItemIcon);
	ItemIcon->SetBrush(Brush);

	ItemCount->SetText(FText::AsNumber(Item.ItemCount));

	Item_0 = Item;
	BackpackComponent_0 = InBackpackComponent;
	Backpack_0 = InBackpack;

	CurrentCharacter = InCharacter;
}

void UBackpack_th::On_ButtonBackground_Clicked()
{
	if (!bUse) return;
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

	if (Item_0.ItemName == "HP_Primary")
	{
		CurrentCharacter->StateComponent->HP += 20;
		if (CurrentCharacter->StateComponent->HP > CurrentCharacter->StateComponent->HP_Max) CurrentCharacter->StateComponent->HP = CurrentCharacter->StateComponent->HP_Max;
	}

	if (Item_0.ItemName == "HP_Advanced")
	{
		CurrentCharacter->StateComponent->HP += 50;
		if (CurrentCharacter->StateComponent->HP > CurrentCharacter->StateComponent->HP_Max) CurrentCharacter->StateComponent->HP = CurrentCharacter->StateComponent->HP_Max;
	}

	if (Item_0.ItemName == "MP_Primary")
	{
		CurrentCharacter->StateComponent->MP += 20;
		if (CurrentCharacter->StateComponent->MP > CurrentCharacter->StateComponent->MP_Max) CurrentCharacter->StateComponent->MP = CurrentCharacter->StateComponent->MP_Max;
	}

	if (Item_0.ItemName == "MP_Advanced")
	{
		CurrentCharacter->StateComponent->MP += 50;
		if (CurrentCharacter->StateComponent->MP > CurrentCharacter->StateComponent->MP_Max) CurrentCharacter->StateComponent->MP = CurrentCharacter->StateComponent->MP_Max;
	}

	Backpack_0->RefreshBackpack();
}

void UBackpack_th::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
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
