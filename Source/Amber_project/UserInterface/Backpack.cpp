// Fill out your copyright notice in the Description page of Project Settings.


#include "Backpack.h"

void UBackpack::SetBackpackComponent(AMainPlayerController* Controller)
{
	if (Controller)
	{
		BackpackComponent = Controller->BackpackComponent;
	}
}

void UBackpack::RefreshBackpack()
{
	if (!BackpackComponent || !GridPanel) return;
	GridPanel->ClearChildren();

	int sum = BackpackComponent->Backpack_Items.Num();	
	int sub = 0;
	for (int h = 0 ; h < 5 ; h++)
	{
		for (int l = 0 ; l < 6 ; l++)
		{
			UBackpack_th* Backpack_Th = CreateWidget<UBackpack_th>(this,BackpackThClass);
			if (sub < sum)
			{
				Backpack_Th->SetItemWidget(BackpackComponent->Backpack_Items[sub],BackpackComponent,this);
				sub++;
			}
			GridPanel->AddChildToUniformGrid(Backpack_Th,h,l);
		}
	}
}
