// Fill out your copyright notice in the Description page of Project Settings.


#include "Store.h"
#include "Store_th.h"
#include "Amber_project/MainPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UStore::NativeConstruct()
{
	Super::NativeConstruct();
	
	StoreItems.Add({"HP_Primary",1,ItemIcon_1,40});
	StoreItems.Add({"HP_Advanced",1,ItemIcon_2,100});
	StoreItems.Add({"MP_Primary",1,ItemIcon_3,40});
	StoreItems.Add({"MP_Advanced",1,ItemIcon_4,100});

	RefreshItem();

	StoreEquipments.Add({"Sword_Iron",EquipIcon_1,0,1,{0,0,5,0},200});
	StoreEquipments.Add({"Staff_Iron",EquipIcon_2,0,2,{0,0,5,0},300});
	StoreEquipments.Add({"Helmet_Iron",EquipIcon_5,1,0,{20,0,0,1},300});
	StoreEquipments.Add({"Armor_Body_Iron",EquipIcon_6,2,0,{50,0,0,2},500});
	StoreEquipments.Add({"Armor_Leg_Iron",EquipIcon_7,3,0,{0,20,0,1},200});
	

	RefreshEquipment();

	Button_Choose_Item->OnClicked.AddDynamic(this, &UStore::ChoosePanel_Item);
	Button_Choose_Equipment->OnClicked.AddDynamic(this, &UStore::ChoosePanel_Equipment);
}

void UStore::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	Text_Describe->SetText(FText::FromStringTable("/Game/Text/Item",Item_Describe));

	Text_Money->SetText(FText::FromString(FString::Printf(TEXT("剩余金币:%.d"),
	Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this,0))->Money)));
}


void UStore::RefreshItem()
{
	int sum = StoreItems.Num();	
	int sub = 0;
	for (int h = 0 ; h < 3 ; h++)
	{
		for (int l = 0 ; l < 3 ; l++)
		{
			UStore_th* Store_th = CreateWidget<UStore_th>(this,StoreThClass);
			if (sub < sum)
			{
				Store_th->SetItemWidget(StoreItems[sub],this);
				Store_th->bUse = true;
				sub++;
			}
			GridPanel_Items->AddChildToUniformGrid(Store_th,h,l);
		}
	}
}

void UStore::RefreshEquipment()
{
	int sum = StoreEquipments.Num();
	int sub = 0;
	for (int h = 0 ; h < 3 ; h++)
	{
		for (int l = 0 ; l < 3 ; l++)
		{
			UStore_Equip* Store_Equip = CreateWidget<UStore_Equip>(this,StoreEquipClass);
			if (sub < sum)
			{
				Store_Equip->SetEquipWidget(StoreEquipments[sub],this);
				Store_Equip->bUse = true;
				sub++;
			}
			GridPanel_Equipment->AddChildToUniformGrid(Store_Equip,h,l);
		}
	}
}


void UStore::ChoosePanel_Item()
{
	PanelSwitcher->SetActiveWidget(Panel_Item);
}

void UStore::ChoosePanel_Equipment()
{
	PanelSwitcher->SetActiveWidget(Panel_Equipment);
}
