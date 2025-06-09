// Fill out your copyright notice in the Description page of Project Settings.


#include "Backpack.h"

#include "Kismet/GameplayStatics.h"

void UBackpack::SetBackpackComponent(AMainPlayerController* Controller)
{
	if (Controller)
	{
		BackpackComponent = Controller->BackpackComponent;
		EquipmentComponent = Controller->EquipmentComponent;
	}
}

void UBackpack::RefreshBackpack()
{
	if (!BackpackComponent) return;
	//清理残留影像
	GridPanel->ClearChildren();
	GridPanel_Equipment->ClearChildren();
	Image_Slot0->SetBrush(FSlateBrush());
	Image_Slot1->SetBrush(FSlateBrush());
	Image_Slot2->SetBrush(FSlateBrush());
	Image_Slot3->SetBrush(FSlateBrush());

	Image_Slot0->SetVisibility(ESlateVisibility::Hidden);
	Image_Slot1->SetVisibility(ESlateVisibility::Hidden);
	Image_Slot2->SetVisibility(ESlateVisibility::Hidden);
	Image_Slot3->SetVisibility(ESlateVisibility::Hidden);

	Button_Slot0->SetVisibility(ESlateVisibility::Hidden);
	Button_Slot1->SetVisibility(ESlateVisibility::Hidden);
	Button_Slot2->SetVisibility(ESlateVisibility::Hidden);
	Button_Slot3->SetVisibility(ESlateVisibility::Hidden);

	AMainPlayerController* MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this,0));
	if (MainPlayerController)
	{
		if (CurrentCharacter == nullptr)
		{
			CurrentCharacter = MainPlayerController->CurrentCharacter;
		}
		if (CurrentCharacter->Character_ID == 1)
		{
			FSlateBrush Brush;
			Brush.SetResourceObject(MainPlayerController->Image_Character_Swordsman);
			Character_Image->SetBrush(Brush);
		}
		if (CurrentCharacter->Character_ID == 2)
		{
			FSlateBrush Brush;
			Brush.SetResourceObject(MainPlayerController->Image_Character_Wizard);
			Character_Image->SetBrush(Brush);
		}
		if (CurrentCharacter->Character_ID == 3)
		{
			FSlateBrush Brush;
			Brush.SetResourceObject(MainPlayerController->Image_Character_Priest);
			Character_Image->SetBrush(Brush);
		}
		if (CurrentCharacter->Character_ID == 4)
		{
			FSlateBrush Brush;
			Brush.SetResourceObject(MainPlayerController->Image_Character_Knight);
			Character_Image->SetBrush(Brush);
		}
	}

	int sum = BackpackComponent->Backpack_Items.Num();	
	int sub = 0;
	//物品列表
	for (int h = 0 ; h < 5 ; h++)
	{
		for (int l = 0 ; l < 6 ; l++)
		{
			UBackpack_th* Backpack_Th = CreateWidget<UBackpack_th>(this,BackpackThClass);
			if (sub < sum)
			{
				Backpack_Th->SetItemWidget(BackpackComponent->Backpack_Items[sub],BackpackComponent,this,CurrentCharacter);
				Backpack_Th->bUse = true;
				sub++;
			}
			GridPanel->AddChildToUniformGrid(Backpack_Th,h,l);
		}
	}

	sum = EquipmentComponent->Equipment.Num();
	sub = 0;
	//装备列表
	for (int h = 0 ; h < 5 ; h++)
	{
		for (int l = 0 ; l < 6 ; l++)
		{
			UBackpack_Equip* Backpack_Equip = CreateWidget<UBackpack_Equip>(this,BackpackEquipClass);
			if (sub < sum)
			{
				Backpack_Equip->SetEquipWidget(EquipmentComponent->Equipment[sub],this,sub,CurrentCharacter);
				Backpack_Equip->bUse = true;
				sub++;
			}
			GridPanel_Equipment->AddChildToUniformGrid(Backpack_Equip,h,l);
		}
	}

	Text_Character_Attributes->SetText(FText::FromString(FString::Printf(TEXT("血量:%.0f/%.0f   蓝量:%.0f/%.0f   攻击力:%.0f    防御力:%.0f"),
	CurrentCharacter->StateComponent->HP,
	CurrentCharacter->StateComponent->HP_Max,
	CurrentCharacter->StateComponent->MP,
	CurrentCharacter->StateComponent->MP_Max,
	CurrentCharacter->StateComponent->Damage,
	CurrentCharacter->StateComponent->Defense)));

	//装备槽的显示
	if (CurrentCharacter->Equipment->Slots[0] == true)
	{
		FSlateBrush Brush_0;
		Brush_0.SetResourceObject(CurrentCharacter->Equipment->Equip_Slot0.ItemIcon);
		Image_Slot0->SetBrush(Brush_0);
		Image_Slot0->SetVisibility(ESlateVisibility::Visible);
		
		Button_Slot0->SetVisibility(ESlateVisibility::Visible);
	}
	if (CurrentCharacter->Equipment->Slots[1] == true)
	{
		FSlateBrush Brush_1;
		Brush_1.SetResourceObject(CurrentCharacter->Equipment->Equip_Slot1.ItemIcon);
		Image_Slot1->SetBrush(Brush_1);
		Image_Slot1->SetVisibility(ESlateVisibility::Visible);

		Button_Slot1->SetVisibility(ESlateVisibility::Visible);
	}
	if (CurrentCharacter->Equipment->Slots[2] == true)
	{
		FSlateBrush Brush_2;
		Brush_2.SetResourceObject(CurrentCharacter->Equipment->Equip_Slot2.ItemIcon);
		Image_Slot2->SetBrush(Brush_2);
		Image_Slot2->SetVisibility(ESlateVisibility::Visible);

		Button_Slot2->SetVisibility(ESlateVisibility::Visible);
	}
	if (CurrentCharacter->Equipment->Slots[3] == true)
	{
		FSlateBrush Brush_3;
		Brush_3.SetResourceObject(CurrentCharacter->Equipment->Equip_Slot3.ItemIcon);
		Image_Slot3->SetBrush(Brush_3);
		Image_Slot3->SetVisibility(ESlateVisibility::Visible);

		Button_Slot3->SetVisibility(ESlateVisibility::Visible);
	}
}

void UBackpack::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	Text_Describe->SetText(FText::FromStringTable("/Game/Text/Item",Item_Describe.ToString()));
}

void UBackpack::NativeConstruct()
{
	Super::NativeConstruct();
	AMainPlayerController* MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this,0));
	if (MainPlayerController)
	{
		CurrentCharacter = MainPlayerController->CurrentCharacter;
	}
	Button_Character_A->OnClicked.AddDynamic(this, &UBackpack::SetCharacter_A);
	Button_Character_B->OnClicked.AddDynamic(this, &UBackpack::SetCharacter_B);

	Button_Choose_Item->OnClicked.AddDynamic(this, &UBackpack::ChoosePanel_Item);
	Button_Choose_Equipment->OnClicked.AddDynamic(this, &UBackpack::ChoosePanel_Equipment);

	Button_Slot0->OnClicked.AddDynamic(this,&UBackpack::On_Button_Slot0_Clicked);
	Button_Slot1->OnClicked.AddDynamic(this,&UBackpack::On_Button_Slot1_Clicked);
	Button_Slot2->OnClicked.AddDynamic(this,&UBackpack::On_Button_Slot2_Clicked);
	Button_Slot3->OnClicked.AddDynamic(this,&UBackpack::On_Button_Slot3_Clicked);

	Button_Remove0->OnClicked.AddDynamic(this,&UBackpack::On_Button_Remove0_Clicked);
	Button_Remove1->OnClicked.AddDynamic(this,&UBackpack::On_Button_Remove1_Clicked);
	Button_Remove2->OnClicked.AddDynamic(this,&UBackpack::On_Button_Remove2_Clicked);
	Button_Remove3->OnClicked.AddDynamic(this,&UBackpack::On_Button_Remove3_Clicked);

	Button_Remove0->SetVisibility(ESlateVisibility::Hidden);
	Button_Remove1->SetVisibility(ESlateVisibility::Hidden);
	Button_Remove2->SetVisibility(ESlateVisibility::Hidden);
	Button_Remove3->SetVisibility(ESlateVisibility::Hidden);
}

void UBackpack::SetCharacter_A()
{
	AMainPlayerController* MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this,0));
	if (MainPlayerController)
	{
		CurrentCharacter = MainPlayerController->CharacterA;
	}
	RefreshBackpack();
}

void UBackpack::SetCharacter_B()
{
	AMainPlayerController* MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this,0));
	if (MainPlayerController)
	{
		CurrentCharacter = MainPlayerController->CharacterB;
	}
	RefreshBackpack();
}

void UBackpack::ChoosePanel_Item()
{
	PanelSwitcher->SetActiveWidget(Panel_Item);
}

void UBackpack::ChoosePanel_Equipment()
{
	PanelSwitcher->SetActiveWidget(Panel_Equipment);
}

void UBackpack::On_Button_Slot0_Clicked()
{
	Button_Remove0->SetVisibility(ESlateVisibility::Visible);
	Item_Describe = CurrentCharacter->Equipment->Equip_Slot0.ItemName;
}

void UBackpack::On_Button_Slot1_Clicked()
{
	Button_Remove1->SetVisibility(ESlateVisibility::Visible);
	Item_Describe = CurrentCharacter->Equipment->Equip_Slot1.ItemName;
}

void UBackpack::On_Button_Slot2_Clicked()
{
	Button_Remove2->SetVisibility(ESlateVisibility::Visible);
	Item_Describe = CurrentCharacter->Equipment->Equip_Slot2.ItemName;
}

void UBackpack::On_Button_Slot3_Clicked()
{
	Button_Remove3->SetVisibility(ESlateVisibility::Visible);
	Item_Describe = CurrentCharacter->Equipment->Equip_Slot3.ItemName;
}


void UBackpack::On_Button_Remove0_Clicked()
{
	//让数值回归
	CurrentCharacter->StateComponent->HP_Max -= CurrentCharacter->Equipment->Equip_Slot0.Attribute[0];
	if (CurrentCharacter->StateComponent->HP > CurrentCharacter->StateComponent->HP_Max)
		CurrentCharacter->StateComponent->HP = CurrentCharacter->StateComponent->HP_Max;
	
	CurrentCharacter->StateComponent->MP_Max -= CurrentCharacter->Equipment->Equip_Slot0.Attribute[1];
	if (CurrentCharacter->StateComponent->MP > CurrentCharacter->StateComponent->MP_Max)
		CurrentCharacter->StateComponent->MP = CurrentCharacter->StateComponent->MP_Max;
	
	CurrentCharacter->StateComponent->Damage -= CurrentCharacter->Equipment->Equip_Slot0.Attribute[2];
	CurrentCharacter->StateComponent->Defense -= CurrentCharacter->Equipment->Equip_Slot0.Attribute[3];

	//让物品从插槽回归背包
	AMainPlayerController* PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this,0));
	if (PlayerController)
	{
		PlayerController->EquipmentComponent->Equipment.Add(CurrentCharacter->Equipment->Equip_Slot0);
	}

	//让物品从插槽消失
	CurrentCharacter->Equipment->Equip_Slot0 = FEquipComponent();
	CurrentCharacter->Equipment->Slots[0] = false;

	Button_Remove0->SetVisibility(ESlateVisibility::Hidden);
	RefreshBackpack();
}

void UBackpack::On_Button_Remove1_Clicked()
{
	CurrentCharacter->StateComponent->HP_Max -= CurrentCharacter->Equipment->Equip_Slot1.Attribute[0];
	if (CurrentCharacter->StateComponent->HP > CurrentCharacter->StateComponent->HP_Max)
		CurrentCharacter->StateComponent->HP = CurrentCharacter->StateComponent->HP_Max;
	
	CurrentCharacter->StateComponent->MP_Max -= CurrentCharacter->Equipment->Equip_Slot1.Attribute[1];
	if (CurrentCharacter->StateComponent->MP > CurrentCharacter->StateComponent->MP_Max)
		CurrentCharacter->StateComponent->MP = CurrentCharacter->StateComponent->MP_Max;
	
	CurrentCharacter->StateComponent->Damage -= CurrentCharacter->Equipment->Equip_Slot1.Attribute[2];
	CurrentCharacter->StateComponent->Defense -= CurrentCharacter->Equipment->Equip_Slot1.Attribute[3];

	AMainPlayerController* PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this,0));
	if (PlayerController)
	{
		PlayerController->EquipmentComponent->Equipment.Add(CurrentCharacter->Equipment->Equip_Slot1);
	}
	
	CurrentCharacter->Equipment->Equip_Slot1 = FEquipComponent();
	CurrentCharacter->Equipment->Slots[1] = false;

	Button_Remove1->SetVisibility(ESlateVisibility::Hidden);
	RefreshBackpack();
}

void UBackpack::On_Button_Remove2_Clicked()
{
	CurrentCharacter->StateComponent->HP_Max -= CurrentCharacter->Equipment->Equip_Slot2.Attribute[0];
	if (CurrentCharacter->StateComponent->HP > CurrentCharacter->StateComponent->HP_Max)
		CurrentCharacter->StateComponent->HP = CurrentCharacter->StateComponent->HP_Max;
	
	CurrentCharacter->StateComponent->MP_Max -= CurrentCharacter->Equipment->Equip_Slot2.Attribute[1];
	if (CurrentCharacter->StateComponent->MP > CurrentCharacter->StateComponent->MP_Max)
		CurrentCharacter->StateComponent->MP = CurrentCharacter->StateComponent->MP_Max;
	
	CurrentCharacter->StateComponent->Damage -= CurrentCharacter->Equipment->Equip_Slot2.Attribute[2];
	CurrentCharacter->StateComponent->Defense -= CurrentCharacter->Equipment->Equip_Slot2.Attribute[3];
	
	AMainPlayerController* PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this,0));
	if (PlayerController)
	{
		PlayerController->EquipmentComponent->Equipment.Add(CurrentCharacter->Equipment->Equip_Slot2);
	}
	
	CurrentCharacter->Equipment->Equip_Slot2 = FEquipComponent();
	CurrentCharacter->Equipment->Slots[2] = false;

	Button_Remove2->SetVisibility(ESlateVisibility::Hidden);
	RefreshBackpack();
}

void UBackpack::On_Button_Remove3_Clicked()
{
	CurrentCharacter->StateComponent->HP_Max -= CurrentCharacter->Equipment->Equip_Slot3.Attribute[0];
	if (CurrentCharacter->StateComponent->HP > CurrentCharacter->StateComponent->HP_Max)
		CurrentCharacter->StateComponent->HP = CurrentCharacter->StateComponent->HP_Max;
	
	CurrentCharacter->StateComponent->MP_Max -= CurrentCharacter->Equipment->Equip_Slot3.Attribute[1];
	if (CurrentCharacter->StateComponent->MP > CurrentCharacter->StateComponent->MP_Max)
		CurrentCharacter->StateComponent->MP = CurrentCharacter->StateComponent->MP_Max;
	
	CurrentCharacter->StateComponent->Damage -= CurrentCharacter->Equipment->Equip_Slot3.Attribute[2];
	CurrentCharacter->StateComponent->Defense -= CurrentCharacter->Equipment->Equip_Slot3.Attribute[3];

	AMainPlayerController* PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this,0));
	if (PlayerController)
	{
		PlayerController->EquipmentComponent->Equipment.Add(CurrentCharacter->Equipment->Equip_Slot3);
	}
	
	CurrentCharacter->Equipment->Equip_Slot3 = FEquipComponent();
	CurrentCharacter->Equipment->Slots[3] = false;

	Button_Remove3->SetVisibility(ESlateVisibility::Hidden);
	RefreshBackpack();
}


