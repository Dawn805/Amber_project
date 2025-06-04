// Fill out your copyright notice in the Description page of Project Settings.


#include "Store_Box.h"

#include "Amber_project/MainPlayerController.h"
#include "Amber_project/Player/MainPaperZDCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AStore_Box::AStore_Box()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&AStore_Box::OnBoxOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this,&AStore_Box::EndBoxOverlap);
}

// Called when the game starts or when spawned
void AStore_Box::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStore_Box::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStore_Box::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainPlayerController* PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this,0));
	if (Cast<AMainPaperZDCharacter>(OtherActor) == PlayerController->CurrentCharacter)
	{
		PlayerController->bOpenStore = true;
	}
}

void AStore_Box::EndBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMainPlayerController* PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this,0));
	if (Cast<AMainPaperZDCharacter>(OtherActor) == PlayerController->CurrentCharacter)
	{
		PlayerController->bOpenStore = false;
	}
}


