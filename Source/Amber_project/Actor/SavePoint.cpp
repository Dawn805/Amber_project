// Fill out your copyright notice in the Description page of Project Settings.


#include "SavePoint.h"

#include "PaperSpriteComponent.h"
#include "Amber_project/MainPlayerController.h"
#include "Amber_project/Player/MainPaperZDCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASavePoint::ASavePoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite");
	RootComponent = SpriteComp;
	BoxComp = CreateDefaultSubobject<UBoxComponent>("Box");
	BoxComp->SetupAttachment(SpriteComp); 
	if (BoxComp)
	{
		BoxComp->OnComponentBeginOverlap.AddDynamic(this,&ASavePoint::OnBoxBeginOverlap);
		BoxComp->OnComponentEndOverlap.AddDynamic(this,&ASavePoint::OnBoxEndOverlap);
	}
}

// Called when the game starts or when spawned
void ASavePoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASavePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASavePoint::OnBoxBeginOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult)
{
	if (Cast<AMainPaperZDCharacter>(Actor))
	{
		AMainPlayerController* PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this,0));
		if (PlayerController)
		{
			PlayerController->bSave = true;
		}
	}
}

void ASavePoint::OnBoxEndOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I)
{
	if (Cast<AMainPaperZDCharacter>(Actor))
	{
		AMainPlayerController* PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this,0));
		if (PlayerController)
		{
			PlayerController->bSave = false;
		}
	}
}


