// Fill out your copyright notice in the Description page of Project Settings.


#include "Backpack_th.h"

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
