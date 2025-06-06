// Fill out your copyright notice in the Description page of Project Settings.


#include "Store_Equip.h"

#include "Amber_project/MainPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UStore_Equip::NativeConstruct()
{
	if (!bUse)
	{
		Button_Buy->SetVisibility(ESlateVisibility::Hidden);
	}

	Button_Buy->OnClicked.AddDynamic(this,&UStore_Equip::AddEquipToBackpack);
}

void UStore_Equip::SetEquipWidget(FEquipComponent InEquip, UStore* InStore)
{
	Equip = InEquip;
	Store = InStore;

	if (Equip.ItemIcon)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(Equip.ItemIcon);
		ItemIcon->SetBrush(Brush);

		Text_Cost->SetText(FText::FromString(FString::Printf(TEXT("%d金币"),Equip.Equip_Cost)));

		Button_EquipToDescribe->OnClicked.AddDynamic(this,&UStore_Equip::Button_EquipToDescribe_OnClicked);
	}
}

void UStore_Equip::AddEquipToBackpack()
{
	AMainPlayerController* PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	if (PlayerController)
	{
		if (PlayerController->Money >= Equip.Equip_Cost)
		{
			PlayerController->Money -= Equip.Equip_Cost;
			PlayerController->EquipmentComponent->Equipment.Add(Equip);
		}
	}
}

void UStore_Equip::Button_EquipToDescribe_OnClicked()
{
	Store->Item_Describe = Equip.ItemName.ToString();
}

