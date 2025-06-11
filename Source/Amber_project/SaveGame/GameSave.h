// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Amber_project/Backpack/BackpackComponent.h"
#include "Amber_project/Backpack/EquipmentComponent.h"
#include "GameFramework/SaveGame.h"
#include "GameSave.generated.h"

/**
 * 
 */

//要存储的东西有：
//人物的位置
//人物的朝向
//人物的ID（当初选的哪两个角色）
//人物当前的属性
//人物当前的装备
//背包里的物品
//背包里的装备

//背包装备
USTRUCT(BlueprintType)
struct FEquipComponent_SaveData
{
	GENERATED_BODY()
//SaveGame存不了图片，这个到时候直接在读档的时候引用
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Slot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Character_ID = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> Attribute;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Equip_Cost;
};

//背包物品
USTRUCT(BlueprintType)
struct FBackpackItem_SaveData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int ItemCount = 1;
};

UCLASS()
class AMBER_PROJECT_API UGameSave : public USaveGame
{
	GENERATED_BODY()

public:
	//人物的位置
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector PlayerLocation;
	//人物的朝向
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FRotator PlayerRotation;
	//人物的编号
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int CharacterID_A;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int CharacterID_B;
	//当前控制角色的ID
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int CharacterID_Current;
	//人物当前的属性HP MP 攻击力 防御力
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<float> Attribute_A;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<float> Attribute_B;
	//人物当前的装备
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<bool> Slot_A = {false,false,false,false};
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FEquipComponent_SaveData Equip_A_Slot0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FEquipComponent_SaveData Equip_A_Slot1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FEquipComponent_SaveData Equip_A_Slot2;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FEquipComponent_SaveData Equip_A_Slot3;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	
	TArray<bool> Slot_B = {false,false,false,false};
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FEquipComponent_SaveData Equip_B_Slot0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FEquipComponent_SaveData Equip_B_Slot1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FEquipComponent_SaveData Equip_B_Slot2;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FEquipComponent_SaveData Equip_B_Slot3;
	//背包的物品
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FBackpackItem_SaveData> Backpack_Items;
	//背包的装备
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FEquipComponent_SaveData> Backpack_Equip;
	//玩家身上的钱
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int Money = 0;

	UFUNCTION(BlueprintCallable)
	void GetEquipInfor(FEquipComponent_SaveData &Equip_A,FEquipComponent &Equip_B);

	UFUNCTION(BlueprintCallable)
	UTexture2D* GetItemIconByName(UDataTable* ItemIconTable, FName ItemName);

	UFUNCTION(BlueprintCallable)
	void SetEquipInfor(FEquipComponent &Equip_A,FEquipComponent_SaveData &Equip_B);
};

void SaveGame(UObject* WorldContextObject);
void LoadGame(UObject* WorldContextObject);
