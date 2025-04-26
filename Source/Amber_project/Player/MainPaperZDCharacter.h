#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Amber_project/Player/Component/StateComponent.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveRightAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveJumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* Attack_JAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* Attack_UAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* Attack_IAction;
	
	virtual void MoveRight(const struct FInputActionInstance& Instance);
	virtual void MoveJump(const struct FInputActionInstance& Instance);
	virtual void Attack_J(const struct FInputActionInstance& Instance);
	virtual void Attack_U(const struct FInputActionInstance& Instance);
	virtual void Attack_I(const struct FInputActionInstance& Instance);

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStateComponent* StateComponent;
};
