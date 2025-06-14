// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSave.h"

#include "Amber_project/MainPlayerController.h"
#include "Amber_project/DataTable/ItemRow.h"
#include "Kismet/GameplayStatics.h"

void SaveGame(UObject* WorldContextObject)
{
	if (!WorldContextObject) return;
	//世界
	UWorld* World = WorldContextObject->GetWorld();
	if (!World) return;
	//控制器
	AMainPlayerController* PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(World, 0));
	if (!PlayerController) return;
	//存档实例
	UGameSave* SaveGameInstance = Cast<UGameSave>(UGameplayStatics::CreateSaveGameObject(UGameSave::StaticClass()));
	if (!SaveGameInstance) return;
	
	//人物的位置
	SaveGameInstance->PlayerLocation = PlayerController->CurrentCharacter->GetActorLocation();
	//人物的朝向
	SaveGameInstance->PlayerRotation = PlayerController->CurrentCharacter->GetActorRotation();
	//角色的ID
	SaveGameInstance->CharacterID_A = PlayerController->CharacterA->Character_ID;
	SaveGameInstance->CharacterID_B = PlayerController->CharacterB->Character_ID;
	//当前控制角色的ID
	SaveGameInstance->CharacterID_Current = PlayerController->CurrentCharacter->Character_ID;
	//人物当前的属性
	SaveGameInstance->Attribute_A.Empty();
	SaveGameInstance->Attribute_A.Add(PlayerController->CharacterA->StateComponent->HP_Max);
	SaveGameInstance->Attribute_A.Add(PlayerController->CharacterA->StateComponent->MP_Max);
	SaveGameInstance->Attribute_A.Add(PlayerController->CharacterA->StateComponent->Damage);
	SaveGameInstance->Attribute_A.Add(PlayerController->CharacterA->StateComponent->Defense);
	SaveGameInstance->Attribute_B.Empty();
	SaveGameInstance->Attribute_B.Add(PlayerController->CharacterB->StateComponent->HP_Max);
	SaveGameInstance->Attribute_B.Add(PlayerController->CharacterB->StateComponent->MP_Max);
	SaveGameInstance->Attribute_B.Add(PlayerController->CharacterB->StateComponent->Damage);
	SaveGameInstance->Attribute_B.Add(PlayerController->CharacterB->StateComponent->Defense);
	//人物当前的装备
	for (int i = 0 ; i < 4 ; i++)
	{
		SaveGameInstance->Slot_A[i] = PlayerController->CharacterA->Equipment->Slots[i];
		if (SaveGameInstance->Slot_A[i] == true)
		{
			if (i == 0) SaveGameInstance->GetEquipInfor(SaveGameInstance->Equip_A_Slot0,PlayerController->CharacterA->Equipment->Equip_Slot0);
			if (i == 1) SaveGameInstance->GetEquipInfor(SaveGameInstance->Equip_A_Slot1,PlayerController->CharacterA->Equipment->Equip_Slot1);
			if (i == 2) SaveGameInstance->GetEquipInfor(SaveGameInstance->Equip_A_Slot2,PlayerController->CharacterA->Equipment->Equip_Slot2);
			if (i == 3) SaveGameInstance->GetEquipInfor(SaveGameInstance->Equip_A_Slot3,PlayerController->CharacterA->Equipment->Equip_Slot3);
		}
	}
	for (int i = 0 ; i < 4 ; i++)
	{
		SaveGameInstance->Slot_B[i] = PlayerController->CharacterB->Equipment->Slots[i];
		if (SaveGameInstance->Slot_B[i] == true)
		{
			if (i == 0) SaveGameInstance->GetEquipInfor(SaveGameInstance->Equip_B_Slot0,PlayerController->CharacterB->Equipment->Equip_Slot0);
			if (i == 1) SaveGameInstance->GetEquipInfor(SaveGameInstance->Equip_B_Slot1,PlayerController->CharacterB->Equipment->Equip_Slot1);
			if (i == 2) SaveGameInstance->GetEquipInfor(SaveGameInstance->Equip_B_Slot2,PlayerController->CharacterB->Equipment->Equip_Slot2);
			if (i == 3) SaveGameInstance->GetEquipInfor(SaveGameInstance->Equip_B_Slot3,PlayerController->CharacterB->Equipment->Equip_Slot3);
		}
	}
	//背包的物品
	SaveGameInstance->Backpack_Items.Empty();
	for (int i = 0 ; i < PlayerController->BackpackComponent->Backpack_Items.Num() ; i++)
	{
		FBackpackItem_SaveData SaveData;
		SaveData.ItemName = PlayerController->BackpackComponent->Backpack_Items[i].ItemName;
		SaveData.ItemCount = PlayerController->BackpackComponent->Backpack_Items[i].ItemCount;
		SaveGameInstance->Backpack_Items.Add(SaveData);
	}
	//背包的装备
	SaveGameInstance->Backpack_Equip.Empty();
	for (int i = 0 ; i < PlayerController->EquipmentComponent->Equipment.Num() ; i++)
	{
		FEquipComponent_SaveData SaveData;
		SaveData.ItemName = PlayerController->EquipmentComponent->Equipment[i].ItemName;
		SaveData.Slot = PlayerController->EquipmentComponent->Equipment[i].Slot;
		SaveData.Character_ID = PlayerController->EquipmentComponent->Equipment[i].Character_ID;
		SaveData.Attribute = PlayerController->EquipmentComponent->Equipment[i].Attribute;
		SaveData.Equip_Cost = PlayerController->EquipmentComponent->Equipment[i].Equip_Cost;
		SaveGameInstance->Backpack_Equip.Add(SaveData);
	}
	//钱
	SaveGameInstance->Money = PlayerController->Money;
	//保存到网盘
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("PlayerSaveSlot"), 0);
}

void LoadGame(UObject* WorldContextObject)
{
	if (!WorldContextObject) return;

	UWorld* World = WorldContextObject->GetWorld();
	if (!World) return;
	
	UGameSave* LoadedGame = Cast<UGameSave>(UGameplayStatics::LoadGameFromSlot(TEXT("PlayerSaveSlot"), 0));
	if (!LoadedGame) return;
	
	AMainPlayerController* PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(World, 0));
	if (!PlayerController) return;
	//解除控制
	PlayerController->UnPossess();
	//销毁现有的角色
	if (PlayerController->CharacterA)
	{
		PlayerController->CharacterA->Destroy();
		PlayerController->CharacterA = nullptr;
	}
	if (PlayerController->CharacterB)
	{
		PlayerController->CharacterB->Destroy();
		PlayerController->CharacterB = nullptr;
	}
	//等下图片的加载从这里面加载
	UDataTable* ItemIconTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/ItemIconDataTable.ItemIconDataTable"));
	//加载角色
	TArray<TSubclassOf<AMainPaperZDCharacter>> SelectedClasses;
	SelectedClasses.Add(PlayerController->SwordsmanClass);
	SelectedClasses.Add(PlayerController->WizardClass);
	SelectedClasses.Add(PlayerController->PriestClass);
	SelectedClasses.Add(PlayerController->KnightClass);

	PlayerController->CharacterA = World->SpawnActor<AMainPaperZDCharacter>(SelectedClasses[LoadedGame->CharacterID_A-1], LoadedGame->PlayerLocation, LoadedGame->PlayerRotation);
	PlayerController->CharacterB = World->SpawnActor<AMainPaperZDCharacter>(SelectedClasses[LoadedGame->CharacterID_B-1], LoadedGame->PlayerLocation, LoadedGame->PlayerRotation);
	PlayerController->CharacterB->SetActorHiddenInGame(true);     
	PlayerController->CharacterB->SetActorEnableCollision(false); 
	PlayerController->CharacterB->SetActorTickEnabled(false);     

	PlayerController->CurrentCharacter = PlayerController->CharacterA;
	PlayerController->AnotherCharacter = PlayerController->CharacterB;

	PlayerController->Possess(PlayerController->CurrentCharacter);

	//加载角色的属性
	PlayerController->CharacterA->StateComponent->HP_Max = LoadedGame->Attribute_A[0];
	PlayerController->CharacterA->StateComponent->HP = LoadedGame->Attribute_A[0];
	PlayerController->CharacterA->StateComponent->MP_Max = LoadedGame->Attribute_A[1];
	PlayerController->CharacterA->StateComponent->MP = LoadedGame->Attribute_A[1];
	PlayerController->CharacterA->StateComponent->Damage = LoadedGame->Attribute_A[2];
	PlayerController->CharacterA->StateComponent->Defense = LoadedGame->Attribute_A[3];

	PlayerController->CharacterB->StateComponent->HP_Max = LoadedGame->Attribute_B[0];
	PlayerController->CharacterB->StateComponent->HP = LoadedGame->Attribute_B[0];
	PlayerController->CharacterB->StateComponent->MP_Max = LoadedGame->Attribute_B[1];
	PlayerController->CharacterB->StateComponent->MP = LoadedGame->Attribute_B[1];
	PlayerController->CharacterB->StateComponent->Damage = LoadedGame->Attribute_B[2];
	PlayerController->CharacterB->StateComponent->Defense = LoadedGame->Attribute_B[3];

	//加载角色装备上的武器
	for (int i = 0 ; i < 4 ; i++)
	{
		PlayerController->CharacterA->Equipment->Slots[i] = LoadedGame->Slot_A[i];
		if (LoadedGame->Slot_A[i] == true)
		{
			if (i == 0) LoadedGame->SetEquipInfor(PlayerController->CharacterA->Equipment->Equip_Slot0,LoadedGame->Equip_A_Slot0);
			if (i == 1) LoadedGame->SetEquipInfor(PlayerController->CharacterA->Equipment->Equip_Slot1,LoadedGame->Equip_A_Slot1);
			if (i == 2) LoadedGame->SetEquipInfor(PlayerController->CharacterA->Equipment->Equip_Slot2,LoadedGame->Equip_A_Slot2);
			if (i == 3) LoadedGame->SetEquipInfor(PlayerController->CharacterA->Equipment->Equip_Slot3,LoadedGame->Equip_A_Slot3);
		}
		
		PlayerController->CharacterB->Equipment->Slots[i] = LoadedGame->Slot_B[i];
		if (LoadedGame->Slot_B[i] == true)
		{
			if (i == 0) LoadedGame->SetEquipInfor(PlayerController->CharacterB->Equipment->Equip_Slot0,LoadedGame->Equip_B_Slot0);
			if (i == 1) LoadedGame->SetEquipInfor(PlayerController->CharacterB->Equipment->Equip_Slot1,LoadedGame->Equip_B_Slot1);
			if (i == 2) LoadedGame->SetEquipInfor(PlayerController->CharacterB->Equipment->Equip_Slot2,LoadedGame->Equip_B_Slot2);
			if (i == 3) LoadedGame->SetEquipInfor(PlayerController->CharacterB->Equipment->Equip_Slot3,LoadedGame->Equip_B_Slot3);
		}
	}

	//加载背包里的武器
	PlayerController->EquipmentComponent->Equipment.Empty();
	for (int i = 0 ; i < LoadedGame->Backpack_Equip.Num() ; i++)
	{
		FEquipComponent Equip;
		Equip.ItemName = LoadedGame->Backpack_Equip[i].ItemName;
		Equip.Slot = LoadedGame->Backpack_Equip[i].Slot;
		Equip.Character_ID = LoadedGame->Backpack_Equip[i].Character_ID;
		Equip.Attribute = LoadedGame->Backpack_Equip[i].Attribute;
		Equip.Equip_Cost = LoadedGame->Backpack_Equip[i].Equip_Cost;

		Equip.ItemIcon = LoadedGame->GetItemIconByName(ItemIconTable,LoadedGame->Backpack_Equip[i].ItemName);

		PlayerController->EquipmentComponent->Equipment.Add(Equip);
	}

	//加载背包里的物品
	PlayerController->BackpackComponent->Backpack_Items.Empty();
	for (int i = 0 ; i < LoadedGame->Backpack_Items.Num() ; i++)
	{
		FBackpackItems Item;
		Item.ItemName = LoadedGame->Backpack_Items[i].ItemName;
		Item.ItemCount = LoadedGame->Backpack_Items[i].ItemCount;

		Item.ItemIcon = LoadedGame->GetItemIconByName(ItemIconTable,Item.ItemName);

		PlayerController->BackpackComponent->Backpack_Items.Add(Item);
	}
	//钱
	PlayerController->Money = LoadedGame->Money;
}	

void UGameSave::GetEquipInfor(FEquipComponent_SaveData &Equip_A, FEquipComponent &Equip_B)
{
	Equip_A.ItemName = Equip_B.ItemName;
	Equip_A.Slot = Equip_B.Slot;
	Equip_A.Character_ID = Equip_B.Character_ID;
	Equip_A.Attribute = Equip_B.Attribute;
	Equip_A.Equip_Cost = Equip_B.Equip_Cost;
}

UTexture2D* UGameSave::GetItemIconByName(UDataTable* ItemIconTable, FName ItemName)
{
	if (!ItemIconTable) return nullptr;
	
	FItemIconRow* Row = ItemIconTable->FindRow<FItemIconRow>(ItemName, TEXT("ItemIcon"));
	if (Row)
	{
		return Row->ItemIcon;
	}
	
	return nullptr;
}

void UGameSave::SetEquipInfor(FEquipComponent &Equip_A, FEquipComponent_SaveData &Equip_B)
{
	Equip_A.ItemName = Equip_B.ItemName;
	Equip_A.Slot = Equip_B.Slot;
	Equip_A.Character_ID = Equip_B.Character_ID;
	Equip_A.Attribute = Equip_B.Attribute;
	Equip_A.Equip_Cost = Equip_B.Equip_Cost;

	//加载图片
	UDataTable* ItemIconTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/ItemIconDataTable.ItemIconDataTable"));
	Equip_A.ItemIcon = GetItemIconByName(ItemIconTable, Equip_A.ItemName);
}
