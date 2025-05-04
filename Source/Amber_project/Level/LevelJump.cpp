// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelJump.h"

#include "Amber_project/Player/MainPaperZDCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ALevelJump::ALevelJump()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComp;

	BoxComp->OnComponentBeginOverlap.AddDynamic(this,&ALevelJump::OnBoxOverlap);
}

// Called when the game starts or when spawned
void ALevelJump::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelJump::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALevelJump::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<AMainPaperZDCharacter>(OtherActor))
	{
		AMainPaperZDCharacter* Player = Cast<AMainPaperZDCharacter>(OtherActor);
		if (JumpLevelName != "No" && OldLevelName != "No")
		{
			FLatentActionInfo Info;
			Info.CallbackTarget = this;
			
			UGameplayStatics::LoadStreamLevel(this,JumpLevelName,true,true,Info);
			UGameplayStatics::UnloadStreamLevel(this,OldLevelName,Info,true);

			FVector PlayerLocation = Player->GetActorLocation();
			Player->SetActorLocation(FVector(StartLocation.X,PlayerLocation.Y,PlayerLocation.Z));
		}
	}
}
