// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

#include "EnhancedInputSubsystems.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(this))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (OpenMenuAction)
		{
			EnhancedInput->BindAction(OpenMenuAction,ETriggerEvent::Started,this,&AMainPlayerController::OpenMenu);
		}
	}
}

void AMainPlayerController::OpenMenu(const struct FInputActionInstance& Instance)
{
	if (MenuWidgetClass && !MenuWidgetInstance)
	{
		MenuWidgetInstance = CreateWidget<UUserWidget>(GetWorld(),MenuWidgetClass);
		if (MenuWidgetInstance)
		{
			MenuWidgetInstance->AddToViewport();

			this->bShowMouseCursor = true;
			this->SetPause(true);
		}
		return;
	}
	if (MenuWidgetInstance)
	{
		MenuWidgetInstance->RemoveFromParent();
		MenuWidgetInstance = nullptr;
		this->bShowMouseCursor = false;
		this->SetPause(false);
	}
}