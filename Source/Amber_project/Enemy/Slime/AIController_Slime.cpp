// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Slime.h"

#include "Amber_project/MainPlayerController.h"
#include "Amber_project/Enemy/MainPaperZDEnemy.h"
#include "Amber_project/Player/MainPaperZDCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


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

	RunBehaviorTree(BehaviorTree);

	AMainPlayerController* MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (MainPlayerController)
	{
		AMainPaperZDCharacter* MainPaperZdCharacter = Cast<AMainPaperZDCharacter>(MainPlayerController->GetCharacter());
		if (MainPaperZdCharacter)
		{
			UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
			if (BlackboardComponent)
			{
				BlackboardComponent->SetValueAsObject("PlayerCharacter",MainPaperZdCharacter);
			}
		}
	}
}

// Called every frame
void AAIController_Slime::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

