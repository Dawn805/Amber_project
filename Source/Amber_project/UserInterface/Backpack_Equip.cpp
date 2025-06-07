// Fill out your copyright notice in the Description page of Project Settings.


#include "Backpack_Equip.h"
#include "HeadMountedDisplayTypes.h"
#include "Amber_project/MainPlayerController.h"
#include "Kismet/GameplayStatics.h"

#include "Backpack.h"

void UBackpack_Equip::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Use->SetVisibility(ESlateVisibility::Hidden);
	Button_Sale->SetVisibility(ESlateVisibility::Hidden);
	if (bUse)
	{
		Button_Show->OnClicked.AddDynamic(this,&UBackpack_Equip::Button_Show_OnClicked);
	}
}

void UBackpack_Equip::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (bButtonShow)
	{
		ThreeSeconds += InDeltaTime;
		if (ThreeSeconds >= 3.0)
		{
			bButtonShow = false;
			ThreeSeconds = 0;
			Button_Use->SetVisibility(ESlateVisibility::Hidden);
			Button_Sale->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UBackpack_Equip::SetEquipWidget(FEquipComponent& InEquipment, UBackpack* InBackpack,int InNumber,AMainPaperZDCharacter* InCharacter)
{
	Equipment = InEquipment;
	Backpack = InBackpack;
	Number = InNumber;
	CurrentCharacter = InCharacter;

	if (Equipment.ItemIcon)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(Equipment.ItemIcon);
		ItemIcon->SetBrush(Brush);

		Button_Use->OnClicked.AddDynamic(this,&UBackpack_Equip::Button_Use_OnClicked);
		Button_Sale->OnClicked.AddDynamic(this,&UBackpack_Equip::Button_Sale_OnClicked);
	}
}

void UBackpack_Equip::Button_Show_OnClicked()
{
	Button_Use->SetVisibility(ESlateVisibility::Visible);
	Button_Sale->SetVisibility(ESlateVisibility::Visible);

	bButtonShow = true;

	Backpack->Item_Describe = Equipment.ItemName;
}

void UBackpack_Equip::Button_Use_OnClicked()
{
	//如果装备不为通用，并且与角色不适配，就会弹出弹窗
	if (Equipment.Character_ID != 0)
	{
		if (CurrentCharacter->Character_ID != Equipment.Character_ID)
		{
			PopupInstance_1 = CreateWidget<UPopup>(GetWorld(),PopupClass_1);
			PopupInstance_1->AddToViewport();
			return;
		}
	}
	//如果当前角色对应装备槽有东西了，就会弹出弹窗
	if (CurrentCharacter->Equipment->Slots[Equipment.Slot] == true)
	{
		PopupInstance_2 = CreateWidget<UPopup>(GetWorld(),PopupClass_2);
		PopupInstance_2->AddToViewport();
		return;
	}

	AMainPlayerController* PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this,0));
	switch(Equipment.Slot)
	{
		case 0:
			CurrentCharacter->Equipment->Equip_Slot0 = Equipment;
			CurrentCharacter->Equipment->Slots[0] = true;
			PlayerController->EquipmentComponent->Equipment.RemoveAt(Number);
		break;

		case 1:
			CurrentCharacter->Equipment->Equip_Slot1 = Equipment;
			CurrentCharacter->Equipment->Slots[1] = true;
			PlayerController->EquipmentComponent->Equipment.RemoveAt(Number);
		break;
		
		case 2:
			CurrentCharacter->Equipment->Equip_Slot2 = Equipment;
			CurrentCharacter->Equipment->Slots[2] = true;
			PlayerController->EquipmentComponent->Equipment.RemoveAt(Number);
		break;
		
		case 3:
			CurrentCharacter->Equipment->Equip_Slot3 = Equipment;
			CurrentCharacter->Equipment->Slots[3] = true;
			PlayerController->EquipmentComponent->Equipment.RemoveAt(Number);
		break;
	}

	CurrentCharacter->StateComponent->HP += Equipment.Attribute[0];
	CurrentCharacter->StateComponent->HP_Max += Equipment.Attribute[0];

	CurrentCharacter->StateComponent->MP += Equipment.Attribute[1];
	CurrentCharacter->StateComponent->MP_Max += Equipment.Attribute[1];

	CurrentCharacter->StateComponent->Damage += Equipment.Attribute[2];

	CurrentCharacter->StateComponent->Defense += Equipment.Attribute[3];

	Backpack->RefreshBackpack();
}

void UBackpack_Equip::Button_Sale_OnClicked()
{
	AMainPlayerController* PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this,0));
	if (PlayerController)
	{
		PlayerController->Money += Equipment.Equip_Cost * 0.7;
		PlayerController->EquipmentComponent->Equipment.RemoveAt(Number);
		
		Button_Use->SetVisibility(ESlateVisibility::Hidden);
		Button_Sale->SetVisibility(ESlateVisibility::Hidden);
		
		Backpack->RefreshBackpack();
	}
}

