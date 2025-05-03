#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Amber_project/Player/Component/StateComponent.h"
#include "GameFramework/Character.h"
#include "MainPaperZDCharacter.generated.h"

UCLASS()
class AMBER_PROJECT_API AMainPaperZDCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	AMainPaperZDCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputAction* MoveRightAction;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputAction* MoveLeftAction;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputAction* MoveJumpAction;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputAction* Attack_JAction;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputAction* Attack_UAction;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputAction* Attack_IAction;

	virtual void MoveLeft(const struct FInputActionInstance& Instance);
	virtual void MoveRight(const struct FInputActionInstance& Instance);
	virtual void MoveJump(const struct FInputActionInstance& Instance);
	virtual void Attack_J(const struct FInputActionInstance& Instance);
	virtual void Attack_U(const struct FInputActionInstance& Instance);
	virtual void Attack_I(const struct FInputActionInstance& Instance);

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStateComponent* StateComponent;

	virtual void OnJumped_Implementation() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName AnimNodeName_Jump = "No";
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName StateMachineName = "No";


public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float FaceDirection = 1.0f;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool AnimRight = true;
};
