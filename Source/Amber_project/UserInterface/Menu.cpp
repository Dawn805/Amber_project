// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"

#include "Amber_project/MainPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"

void UMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Continue)
		Button_Continue->OnClicked.AddDynamic(this,&UMenu::Button_Continue_OnClicked);
	if (Button_Settings)
		Button_Settings->OnClicked.AddDynamic(this,&UMenu::Button_Settings_OnClicked);
	if (Button_Exit)
		Button_Exit->OnClicked.AddDynamic(this,&UMenu::UMenu::Button_Exit_OnClicked);
	if (Button_LoadGame)
		Button_LoadGame->OnClicked.AddDynamic(this,&UMenu::Button_LoadGame_OnClicked);
}

void UMenu::Button_Continue_OnClicked()
{
	if (class AMainPlayerController* MainPlayerController = Cast<AMainPlayerController>(GetOwningPlayer()))
	{
		MainPlayerController->CloseMenu();
	}
}

void UMenu::Button_Exit_OnClicked()
{
	UKismetSystemLibrary::QuitGame(this,nullptr,EQuitPreference::Quit,true);
}

void UMenu::Button_Settings_OnClicked()
{
	if (AMainPlayerController* MainPlayerController = Cast<AMainPlayerController>(GetOwningPlayer()))
	{
		MainPlayerController->OpenSettings();
	}
}

void UMenu::Button_LoadGame_OnClicked()
{
	AMainPlayerController* MainPlayerController = Cast<AMainPlayerController>(GetOwningPlayer());
	MainPlayerController->LoadGameFunction();
}
