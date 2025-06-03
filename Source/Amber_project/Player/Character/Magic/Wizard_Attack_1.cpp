// Fill out your copyright notice in the Description page of Project Settings.


#include "Wizard_Attack_1.h"


// Sets default values
AWizard_Attack_1::AWizard_Attack_1()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FlipbookComponent_1 = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipbookComponent_1"));
	RootComponent = FlipbookComponent_1;

	PaperZDAnimationComponent_1 = CreateDefaultSubobject<UPaperZDAnimationComponent>(TEXT("PaperZDAnimationComponent_1"));
}

// Called when the game starts or when spawned
void AWizard_Attack_1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWizard_Attack_1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

