// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputComponent.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputMappingContext* InputMapping;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputAction* OpenMenuAction;

	UFUNCTION(BlueprintCallable)
	void OpenMenu(const struct FInputActionInstance& Instance);

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UUserWidget> MenuWidgetClass;
	UPROPERTY(EditAnywhere)
	UUserWidget* MenuWidgetInstance = nullptr;
};
