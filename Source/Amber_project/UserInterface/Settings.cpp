// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings.h"

#include "Amber_project/MainPlayerController.h"

void USettings::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_KeysChange)
		Button_KeysChange->OnClicked.AddDynamic(this,&USettings::Button_KeysChange_OnClicked);
	if (Button_Sound)
		Button_Sound->OnClicked.AddDynamic(this,&USettings::Button_Sound_OnClicked);
	if (Button_ComeBack)
		Button_ComeBack->OnClicked.AddDynamic(this,&USettings::Button_Come_Back_OnClicked);
}

void USettings::Button_KeysChange_OnClicked()
{
	
}

void USettings::Button_Sound_OnClicked()
{
	
}

void USettings::Button_Come_Back_OnClicked()
{
	if (AMainPlayerController* MainPlayerController = Cast<AMainPlayerController>(GetOwningPlayer()))
	{
		MainPlayerController->CloseSettings();
	}
}
