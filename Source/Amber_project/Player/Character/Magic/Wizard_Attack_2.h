// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimationComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Wizard_Attack_2.generated.h"

UCLASS()
class AMBER_PROJECT_API AWizard_Attack_2 : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWizard_Attack_2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UPaperFlipbookComponent* FlipbookComponent_2;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBoxComponent* BoxComponent_2;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UPaperZDAnimationComponent* AnimationComponent_2;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovementComponent_2;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float FlySpeed = 10.0f;
};
