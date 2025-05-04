// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Slime.h"


// Sets default values
AAIController_Slime::AAIController_Slime()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAIController_Slime::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIController_Slime::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

