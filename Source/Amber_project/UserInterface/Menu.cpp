// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"

#include "Amber_project/MainPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"

void UMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Continue)
	{
		Button_Continue->OnClicked.AddDynamic(this,&UMenu::Button_Continue_OnClicked);
	}

	if (Button_Exit)
	{
		Button_Exit->OnClicked.AddDynamic(this,&UMenu::UMenu::Button_Exit_OnClicked);
	}
}

void UMenu::Button_Continue_OnClicked()
{
	this->RemoveFromParent();
	if (class AMainPlayerController* MainPlayerController = Cast<AMainPlayerController>(GetOwningPlayer()))
	{
		MainPlayerController->MenuWidgetInstance = nullptr;
		MainPlayerController->bShowMouseCursor = false;
		MainPlayerController->SetPause(false);
	}
}

void UMenu::Button_Exit_OnClicked()
{
	UKismetSystemLibrary::QuitGame(this,nullptr,EQuitPreference::Quit,true);
}