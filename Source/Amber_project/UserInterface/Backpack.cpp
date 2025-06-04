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
		if (CurrentCharacter->Character_ID == 4)
		{
			FSlateBrush Brush;
			Brush.SetResourceObject(MainPlayerController->Image_Character_Wizard);
			Character_Image->SetBrush(Brush);
		}
	}

	int sum = BackpackComponent->Backpack_Items.Num();	
	int sub = 0;
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

	Text_Character_Attributes->SetText(FText::FromString(FString::Printf(TEXT("血量:%.0f/%.0f   蓝量:%.0f/%.0f   攻击力:%.0f    防御力:%.0f"),
	CurrentCharacter->StateComponent->HP,
	CurrentCharacter->StateComponent->HP_Max,
	CurrentCharacter->StateComponent->MP,
	CurrentCharacter->StateComponent->MP_Max,
	CurrentCharacter->StateComponent->Damage,
	CurrentCharacter->StateComponent->Defense)));
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