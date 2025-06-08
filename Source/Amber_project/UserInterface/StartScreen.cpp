// Fill out your copyright notice in the Description page of Project Settings.


#include "StartScreen.h"

#include "Amber_project/MainPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UStartScreen::NativeConstruct()
{
	Button_StartGame->OnClicked.AddDynamic(this,&UStartScreen::On_StartGame_Clicked);
	Button_ContinueGame->OnClicked.AddDynamic(this,&UStartScreen::On_ContinueGame_Clicked);
	Button_Settings->OnClicked.AddDynamic(this,&UStartScreen::On_Settings_Clicked);
	Button_ExitGame->OnClicked.AddDynamic(this,&UStartScreen::On_ExitGame_Clicked);

	Button_ContinueGame->SetVisibility(ESlateVisibility::Hidden);
}

void UStartScreen::On_StartGame_Clicked()
{
	if (SelectCharacterClass && !SelectCharacterInstance)
	{
		SelectCharacterInstance = CreateWidget<USelectCharacter>(GetWorld(),SelectCharacterClass);
		SelectCharacterInstance->AddToViewport();
	}
}

void UStartScreen::On_ContinueGame_Clicked()
{
	
}

void UStartScreen::On_Settings_Clicked()
{
	AMainPlayerController* PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this,0));
	if (PlayerController->SettingsWidgetClass && !PlayerController->SettingsWidgetInstance)
	{
		PlayerController->SettingsWidgetInstance = CreateWidget<UUserWidget>(GetWorld(),PlayerController->SettingsWidgetClass);
		if (PlayerController->SettingsWidgetInstance)
		{
			PlayerController->SettingsWidgetInstance->AddToViewport();
		}
		if (PlayerController->MenuWidgetInstance)
		{
			PlayerController->MenuWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UStartScreen::On_ExitGame_Clicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}




