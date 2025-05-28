// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "Amber_project/MainPlayerController.h"
#include "Amber_project/Player/MainPaperZDCharacter.h"


// Sets default values
AItem::AItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ItemSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Item"));
	RootComponent = ItemSprite;

	ItemSprite->SetGenerateOverlapEvents(true);
	ItemSprite->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ItemSprite->SetCollisionObjectType(ECC_WorldDynamic);
	ItemSprite->SetCollisionResponseToAllChannels(ECR_Ignore);
	ItemSprite->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (AMainPaperZDCharacter* ZDCharacter = Cast<AMainPaperZDCharacter>(OtherActor))
	{
		AMainPlayerController* ZDController = Cast<AMainPlayerController>(ZDCharacter->GetController());
		FBackpackItems ThisItem = {ItemName,ItemCount,ItemIcon};
		ZDController->BackpackComponent->AddItem(ThisItem);

		this->Destroy();
	}
}

