// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimationComponent.h"
#include "GameFramework/Actor.h"
#include "Wizard_Attack_1.generated.h"

UCLASS()
class AMBER_PROJECT_API AWizard_Attack_1 : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWizard_Attack_1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UPaperFlipbookComponent* FlipbookComponent_1;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UPaperZDAnimationComponent* PaperZDAnimationComponent_1;
};
