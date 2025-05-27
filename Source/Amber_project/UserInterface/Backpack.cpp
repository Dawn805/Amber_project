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

	int h = 0;
	int l = 0;

	for (int i = 0 ; i < BackpackComponent->Backpack_Items.Num(); i++)
	{
		UBackpack_th* Backpack_Th = CreateWidget<UBackpack_th>(this,BackpackThClass);
		if (Backpack_Th)
		{
			Backpack_Th->SetItemWidget(BackpackComponent->Backpack_Items[i],BackpackComponent,this);
			GridPanel->AddChildToUniformGrid(Backpack_Th,h,l);
			h++;
			if (h >= 6)
			{
				h = 0;
				l++;
			}
		}
	}
}
