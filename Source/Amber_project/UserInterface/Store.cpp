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
