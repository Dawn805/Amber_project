// Fill out your copyright notice in the Description page of Project Settings.


#include "Backpack.h"

#include "Kismet/GameplayStatics.h"

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
				Backpack_Th->bUse = true;
				sub++;
			}
			GridPanel->AddChildToUniformGrid(Backpack_Th,h,l);
		}
	}

	AMainPlayerController* MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this,0));
	if (MainPlayerController)
	{
		AMainPaperZDCharacter* ZdCharacter = Cast<AMainPaperZDCharacter>(MainPlayerController->GetPawn());
		if (ZdCharacter->Character_ID == 1)
		{
			FSlateBrush Brush;
			Brush.SetResourceObject(MainPlayerController->Image_Character_Swordsman);
			Character_Image->SetBrush(Brush);
		}
		if (ZdCharacter->Character_ID == 4)
		{
			FSlateBrush Brush;
			Brush.SetResourceObject(MainPlayerController->Image_Character_Wizard);
			Character_Image->SetBrush(Brush);
		}
	}
}
