// Fill out your copyright notice in the Description page of Project Settings.


#include "StartScreen.h"

#include "Amber_project/MainPlayerController.h"
#include "Amber_project/SaveGame/GameSave.h"
#include "Kismet/GameplayStatics.h"

void UStartScreen::NativeConstruct()
{
	Button_StartGame->OnClicked.AddDynamic(this,&UStartScreen::On_StartGame_Clicked);
	Button_ContinueGame->OnClicked.AddDynamic(this,&UStartScreen::On_ContinueGame_Clicked);
	Button_Settings->OnClicked.AddDynamic(this,&UStartScreen::On_Settings_Clicked);
	Button_ExitGame->OnClicked.AddDynamic(this,&UStartScreen::On_ExitGame_Clicked);

	Button_ContinueGame->SetVisibility(ESlateVisibility::Hidden);

	if (UGameplayStatics::DoesSaveGameExist(TEXT("PlayerSaveSlot"), 0))
	{
		Button_ContinueGame->SetVisibility(ESlateVisibility::Visible);
	}
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
	if (UGameplayStatics::DoesSaveGameExist(TEXT("PlayerSaveSlot"), 0))
	{
		LoadGame(this);
		AMainPlayerController* PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this,0));
		if (PlayerController)
		{
			PlayerController->bStart = true;
			PlayerController->SetPause(false);
			PlayerController->bShowMouseCursor = false;
		}

		//给角色添加PlayerState
		UWorld* World = GetWorld();
		if (World)
		{
			FString MapName = World->GetMapName();
			MapName.RemoveFromStart(World->StreamingLevelsPrefix);
			if (PlayerController->PlayerStateWidgetClass)
			{
				PlayerController->PlayerStateWidgetInstance = CreateWidget<UPlayerStateWidget>(this, PlayerController->PlayerStateWidgetClass);
				if (PlayerController->PlayerStateWidgetInstance)
				{
					PlayerController->PlayerStateWidgetInstance->PlayerController = PlayerController;
					PlayerController->PlayerStateWidgetInstance->AddToViewport();
				}
			}
		
		}
	}
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




