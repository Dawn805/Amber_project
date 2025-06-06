// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSprite.h"
#include "Components/ActorComponent.h"
#include "EquipmentComponent.generated.h"

USTRUCT(BlueprintType)
struct FEquipComponent
{
	GENERATED_BODY()

public:
	//传统两件套，名字和图片
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* ItemIcon;
	//插槽，因为装备栏一共有四个格子，Slot1是武器，2是头盔，3是身甲，4是鞋子
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int Slot;
	//当ID为0的时候所有角色都能使用，其次比如1为Swordsman专属，2为Wizard专属
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int Character_ID = 0;
	//我想这数组为0是HP，1是MP.2是攻击力，3是防御力，用于给角色增添属性
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<float> Attribute;
	//售出系统，因为这个药水不同，不设置ItemCount，多了肯定会臃肿，所以多了直接半价卖了，商店原价买
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int Equip_Cost;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AMBER_PROJECT_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEquipmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;


//这玩意和背包物品不同，装备好像在这里写添加和使用有点不合适
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEquipComponent> Equipment;
};
