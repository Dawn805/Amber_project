// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

#include "Player/MainPaperZDCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/Backpack.h"

AMainPlayerController::AMainPlayerController()
{
	BackpackComponent = CreateDefaultSubobject<UBackpackComponent>(TEXT("Backpack"));	
}

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

	InitKeySave();
	
//切换角色尝试
	FVector SpawnLoc = FVector(20, 0, 0);
	FRotator SpawnRot = FRotator::ZeroRotator;

	CharacterA = GetWorld()->SpawnActor<AMainPaperZDCharacter>(SwordsmanClass, SpawnLoc, SpawnRot);
	CharacterB = GetWorld()->SpawnActor<AMainPaperZDCharacter>(WizardClass, SpawnLoc, SpawnRot);
	CharacterB->SetActorHiddenInGame(true);     
	CharacterB->SetActorEnableCollision(false); 
	CharacterB->SetActorTickEnabled(false);     

	CurrentCharacter = CharacterA;
	AnotherCharacter = CharacterB;

	Possess(CurrentCharacter);

	
//给角色添加PlayerState
	UWorld* World = GetWorld();
	if (World)
	{
		FString MapName = World->GetMapName();
		MapName.RemoveFromStart(World->StreamingLevelsPrefix);
		if (PlayerStateWidgetClass)
		{
			PlayerStateWidgetInstance = CreateWidget<UPlayerStateWidget>(this, PlayerStateWidgetClass);
			if (PlayerStateWidgetInstance)
			{
				PlayerStateWidgetInstance->PlayerController = this;
				PlayerStateWidgetInstance->AddToViewport();
			}
		}
		
	}
}

void AMainPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentCharacter->StateComponent->HP <= 0)
	{
		if (AnotherCharacter->StateComponent->HP > 0)
		{
			CurrentCharacter->StateComponent->HP = 0;
			SwitchCharacter();
		}
	}
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (OpenMenuAction)
			EnhancedInput->BindAction(OpenMenuAction,ETriggerEvent::Started,this,&AMainPlayerController::OpenMenu);
		if (SwitchCharacterAction)
			EnhancedInput->BindAction(SwitchCharacterAction,ETriggerEvent::Started,this,&AMainPlayerController::SwitchCharacter);
		if (OpenBackpackAction)
			EnhancedInput->BindAction(OpenBackpackAction,ETriggerEvent::Started,this,&AMainPlayerController::OpenBackpack);
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
		CloseMenu();
	}
}

void AMainPlayerController::CloseMenu()
{
	if (MenuWidgetInstance)
	{
		MenuWidgetInstance->RemoveFromParent();
		MenuWidgetInstance = nullptr;
	}

	if (SettingsWidgetInstance)
	{
		SettingsWidgetInstance->RemoveFromParent();
		SettingsWidgetInstance = nullptr;
	}
		
	this->bShowMouseCursor = false;
	this->SetPause(false);
}

void AMainPlayerController::OpenSettings()
{
	if (SettingsWidgetClass && !SettingsWidgetInstance)
	{
		SettingsWidgetInstance = CreateWidget<UUserWidget>(GetWorld(),SettingsWidgetClass);
		if (SettingsWidgetInstance)
		{
			SettingsWidgetInstance->AddToViewport();
		}
		if (MenuWidgetInstance)
		{
			MenuWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
void AMainPlayerController::CloseSettings()
{
	if (SettingsWidgetInstance)
	{
		SettingsWidgetInstance->RemoveFromParent();
		SettingsWidgetInstance = nullptr;
	}
	
	if (MenuWidgetInstance)
	{
		MenuWidgetInstance->SetVisibility(ESlateVisibility::Visible);
	}
}


void AMainPlayerController::InitKeySave()
{
	UKeySaveLibrary::CreateSave();

	TMap<int,FKey> KeyMap = UKeySaveLibrary::GetStatKeyMap();
	if (KeyMap.IsEmpty())
	{
		UKeySaveLibrary::ResetStatKeyMap();
	}
}

void AMainPlayerController::SwitchCharacter()
{
	if (!CurrentCharacter || !AnotherCharacter) return;

	FVector LastLocation = CurrentCharacter->GetActorLocation();
	FRotator LastRotation = CurrentCharacter->FindComponentByClass<UPaperFlipbookComponent>()->GetRelativeRotation();
	FVector LastVelocity = CurrentCharacter->GetCharacterMovement()->Velocity;

	CurrentCharacter->SetActorHiddenInGame(true);
	CurrentCharacter->SetActorEnableCollision(false);
	CurrentCharacter->SetActorTickEnabled(false);

	AnotherCharacter->SetActorLocation(LastLocation);
	AnotherCharacter->FindComponentByClass<UPaperFlipbookComponent>()->SetRelativeRotation(LastRotation);
	if (LastVelocity.Size() > AnotherCharacter->GetCharacterMovement()->MaxWalkSpeed)
	{
		LastVelocity = LastVelocity.GetSafeNormal() * AnotherCharacter->GetCharacterMovement()->MaxWalkSpeed;
	}
	AnotherCharacter->GetCharacterMovement()->Velocity = LastVelocity;
	
	AnotherCharacter->SetActorHiddenInGame(false);
	AnotherCharacter->SetActorEnableCollision(true);
	AnotherCharacter->SetActorTickEnabled(true);

	Possess(AnotherCharacter);

	Swap(CurrentCharacter, AnotherCharacter);
}

void AMainPlayerController::OpenBackpack()
{
	if (MenuWidgetInstance) return;
	if (BackpackWidgetClass && !BackpackWidgetInstance)
	{
		BackpackWidgetInstance = CreateWidget<UBackpack>(GetWorld(),BackpackWidgetClass);
		if (BackpackWidgetInstance)
		{
			BackpackWidgetInstance->SetBackpackComponent(this);
			BackpackWidgetInstance->RefreshBackpack();
			BackpackWidgetInstance->AddToViewport();
			this->bShowMouseCursor = true;
			this->SetPause(true);
		}
		return;
	}
	if (BackpackWidgetInstance)
	{
		CloseBackpack();
	}
}

void AMainPlayerController::CloseBackpack()
{
	if (BackpackWidgetInstance)
	{
		BackpackWidgetInstance->RemoveFromParent();
		BackpackWidgetInstance = nullptr;
		this->bShowMouseCursor = false;
		this->SetPause(false);
	}
}

