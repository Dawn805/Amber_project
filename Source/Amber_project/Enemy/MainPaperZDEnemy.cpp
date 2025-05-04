// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPaperZDEnemy.h"

#include "PaperFlipbookComponent.h"


// Sets default values
AMainPaperZDEnemy::AMainPaperZDEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMainPaperZDEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainPaperZDEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Velocity = GetVelocity();
	if (FMath::Abs(Velocity.X) > 0.0f)
	{
		float Scale = 1.0f;
		if (Velocity.X > 0.0f) Scale = 1.0f;
		if (Velocity.X < 0.0f) Scale = -1.0f;
		GetSprite()->SetRelativeScale3D(FVector(Scale, 1.0f, 1.0f));
	}
}

// Called to bind functionality to input
void AMainPaperZDEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

