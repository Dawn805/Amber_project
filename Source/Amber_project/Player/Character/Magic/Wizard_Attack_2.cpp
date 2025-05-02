// Fill out your copyright notice in the Description page of Project Settings.


#include "Wizard_Attack_2.h"

#include "PaperZDAnimInstance.h"


// Sets default values
AWizard_Attack_2::AWizard_Attack_2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FlipbookComponent_2 = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	BoxComponent_2 = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	AnimationComponent_2 = CreateDefaultSubobject<UPaperZDAnimationComponent>(TEXT("AnimationComponent"));
}

// Called when the game starts or when spawned
void AWizard_Attack_2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWizard_Attack_2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

