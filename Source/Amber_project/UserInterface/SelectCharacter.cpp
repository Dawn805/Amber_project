// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectCharacter.h"

#include "Amber_project/MainPlayerController.h"
#include "Kismet/GameplayStatics.h"

void USelectCharacter::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Sword->OnClicked.AddDynamic(this,&USelectCharacter::OnSelectSwordsman);
	Button_Wizard->OnClicked.AddDynamic(this,&USelectCharacter::OnSelectWizard);
	Button_Priest->OnClicked.AddDynamic(this,&USelectCharacter::OnSelectPriest);
	Button_OnConfirmSelection->OnClicked.AddDynamic(this,&USelectCharacter::OnConfirmSelection);
}

void USelectCharacter::OnSelectSwordsman()
{
	if (SelectedClasses.Contains(SwordsmanClass)) return;
	if (SelectedClasses.Num() >= 2) return;
	SelectedClasses.Add(SwordsmanClass);
}

void USelectCharacter::OnSelectWizard()
{
	if (SelectedClasses.Contains(WizardClass)) return;
	if (SelectedClasses.Num() >= 2) return;
	SelectedClasses.Add(WizardClass);
}

void USelectCharacter::OnSelectPriest()
{
	if (SelectedClasses.Contains(PriestClass)) return;
	if (SelectedClasses.Num() >= 2) return;
	SelectedClasses.Add(PriestClass);
}

void USelectCharacter::OnConfirmSelection()
{
	AMainPlayerController* PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this,0));
	
	FVector SpawnLoc = FVector(20, 0, 0);
	FRotator SpawnRot = FRotator::ZeroRotator;

	PlayerController->CharacterA = GetWorld()->SpawnActor<AMainPaperZDCharacter>(SelectedClasses[0], SpawnLoc, SpawnRot);
	PlayerController->CharacterB = GetWorld()->SpawnActor<AMainPaperZDCharacter>(SelectedClasses[1], SpawnLoc, SpawnRot);
	PlayerController->CharacterB->SetActorHiddenInGame(true);     
	PlayerController->CharacterB->SetActorEnableCollision(false); 
	PlayerController->CharacterB->SetActorTickEnabled(false);     

	PlayerController->CurrentCharacter = PlayerController->CharacterA;
	PlayerController->AnotherCharacter = PlayerController->CharacterB;

	PlayerController->Possess(PlayerController->CurrentCharacter);

	
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

	PlayerController->SetPause(false);
	PlayerController->bShowMouseCursor = false;
	
	PlayerController->bStart = true;
}
