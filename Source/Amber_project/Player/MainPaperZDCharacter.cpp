#include "MainPaperZDCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimInstance.h"

AMainPaperZDCharacter::AMainPaperZDCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	StateComponent = CreateDefaultSubobject<UStateComponent>("StateComponent");
}

void AMainPaperZDCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
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
		}
		else if (Value < 0.0f && SpriteComponent)
		{
			SpriteComponent->SetRelativeRotation(FRotator(0, -180, 0));
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
	if (FAnimInstance && AnimNodeName_Jump != "No" && StateMachineName != "No")
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
