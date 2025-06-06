// Fill out your copyright notice in the Description page of Project Settings.


#include "Backpack_Equip.h"

void UBackpack_Equip::SetEquipWidget(FEquipComponent& InEquipment, UBackpack* InBackpack)
{
	Equipment = InEquipment;
	Backpack = InBackpack;
	
	FSlateBrush Brush;
	Brush.SetResourceObject(Equipment.ItemIcon);
	ItemIcon->SetBrush(Brush);
}
