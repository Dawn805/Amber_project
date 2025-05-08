#include "MainPaperZDCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimInstance.h"
#include "Amber_project/UserInterface/Component/KeySaveLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

AMainPaperZDCharacter::AMainPaperZDCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	StateComponent = CreateDefaultSubobject<UStateComponent>("StateComponent");
}

void AMainPaperZDCharacter::BeginPlay()
{
	Super::BeginPlay();

	UKeySaveLibrary::CreateSave();
	TMap<int,FKey> LoadedKeyMap = UKeySaveLibrary::GetStatKeyMap();
	UInputMappingContext* NewMappingContext = NewObject<UInputMappingContext>(this);

	for (int i = 0 ; i < InputMappingContext->GetMappings().Num() ; i++)
	{
		NewMappingContext->MapKey(InputMappingContext->GetMappings()[i].Action,LoadedKeyMap[i]);
	}
	
	
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			//Subsystem->RemoveMappingContext(InputMappingContext);
			Subsystem->AddMappingContext(NewMappingContext, 1);
		}
	}
}

void AMainPaperZDCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainPaperZDCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (MoveRightAction)
			EnhancedInput->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &AMainPaperZDCharacter::MoveRight);
		if (MoveLeftAction)
			EnhancedInput->BindAction(MoveLeftAction, ETriggerEvent::Triggered, this,&AMainPaperZDCharacter::MoveLeft);
		if (MoveJumpAction)
			EnhancedInput->BindAction(MoveJumpAction, ETriggerEvent::Started, this, &AMainPaperZDCharacter::Jump);
		if (Attack_JAction)
			EnhancedInput->BindAction(Attack_JAction, ETriggerEvent::Started, this, &AMainPaperZDCharacter::Attack_J);
		if (Attack_UAction)
			EnhancedInput->BindAction(Attack_UAction, ETriggerEvent::Started, this, &AMainPaperZDCharacter::Attack_U);
		if (Attack_IAction)
			EnhancedInput->BindAction(Attack_IAction, ETriggerEvent::Started, this, &AMainPaperZDCharacter::Attack_I);
	}
}

void AMainPaperZDCharacter::MoveLeft(const FInputActionInstance& Instance)
{
	const float Value = Instance.GetValue().Get<float>();
	if (Value && Controller)
	{
		const FRotator Rotator = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotator).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, -Value);

		UPaperFlipbookComponent* SpriteComponent = this->FindComponentByClass<UPaperFlipbookComponent>();
		if (Value < 0.0f && SpriteComponent)
		{
			SpriteComponent->SetRelativeRotation(FRotator(0, 0, 0));

			FaceDirection = 1.0f;
		}
		else if (Value > 0.0f && SpriteComponent)
		{
			SpriteComponent->SetRelativeRotation(FRotator(0, -180, 0));

			FaceDirection = -1.0f;
		}
	}
}

void AMainPaperZDCharacter::MoveRight(const FInputActionInstance& Instance)
{
	const float Value = Instance.GetValue().Get<float>();
	if (Value && Controller)
	{
		const FRotator Rotator = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotator).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);

		UPaperFlipbookComponent* SpriteComponent = this->FindComponentByClass<UPaperFlipbookComponent>();
		if (Value > 0.0f && SpriteComponent)
		{
			SpriteComponent->SetRelativeRotation(FRotator(0, 0, 0));

			FaceDirection = 1.0f;
		}
		else if (Value < 0.0f && SpriteComponent)
		{
			SpriteComponent->SetRelativeRotation(FRotator(0, -180, 0));

			FaceDirection = -1.0f;
		}
	}
}

void AMainPaperZDCharacter::MoveJump(const struct FInputActionInstance& Instance)
{
	Super::Jump();
}

void AMainPaperZDCharacter::OnJumped_Implementation()
{
	UPaperZDAnimInstance* FAnimInstance = this->GetAnimInstance();
	if (FAnimInstance && AnimNodeName_Jump != "No" && StateMachineName != "No" && AnimRight)
	{
		FAnimInstance->JumpToNode(AnimNodeName_Jump,StateMachineName);
	}
}


void AMainPaperZDCharacter::Attack_J(const FInputActionInstance& Instance)
{
	
}

void AMainPaperZDCharacter::Attack_U(const FInputActionInstance& Instance)
{
	
}

void AMainPaperZDCharacter::Attack_I(const FInputActionInstance& Instance)
{
	
}
