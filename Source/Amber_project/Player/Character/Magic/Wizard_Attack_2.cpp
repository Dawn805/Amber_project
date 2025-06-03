// Fill out your copyright notice in the Description page of Project Settings.


#include "Wizard_Attack_2.h"

#include "PaperZDAnimInstance.h"
#include "Amber_project/Enemy/MainPaperZDEnemy.h"
#include "Amber_project/Player/MainPaperZDCharacter.h"


// Sets default values
AWizard_Attack_2::AWizard_Attack_2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent_2 = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent_2;
	
	FlipbookComponent_2 = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	FlipbookComponent_2->SetupAttachment(BoxComponent_2);
	
	AnimationComponent_2 = CreateDefaultSubobject<UPaperZDAnimationComponent>(TEXT("AnimationComponent"));
	
	ProjectileMovementComponent_2 = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	ProjectileMovementComponent_2->SetUpdatedComponent(BoxComponent_2);
	
	InitialLifeSpan = 2.5f;
	
	ProjectileMovementComponent_2->ProjectileGravityScale = 0.0f;

	BoxComponent_2->OnComponentBeginOverlap.AddDynamic(this,&AWizard_Attack_2::BeginOverlap);
}

// Called when the game starts or when spawned
void AWizard_Attack_2::BeginPlay()
{
	Super::BeginPlay();

	AMainPaperZDCharacter* Master = Cast<AMainPaperZDCharacter>(GetOwner());
	if (Master)
	{
		float D = Master->FaceDirection;

		UPaperFlipbookComponent* SpriteComponent = this->FindComponentByClass<UPaperFlipbookComponent>();
		
		if (D == -1.0f)
		{
			SpriteComponent->SetRelativeRotation(FRotator(0, -180, 0));
		}else
		{
			SpriteComponent->SetRelativeRotation(FRotator(0, 0, 0));
		}

		ProjectileMovementComponent_2->Velocity = FVector(FlySpeed*D, 0, 0);
	}
	
}

// Called every frame
void AWizard_Attack_2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWizard_Attack_2::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMainPaperZDEnemy>(OtherActor))
	{
		UPaperZDAnimInstance* FAnimInstance = AnimationComponent_2->GetAnimInstance();
		FAnimInstance->JumpToNode("Boom","Locomotion");
		ProjectileMovementComponent_2->Velocity = FVector(0,0,0);
	}
}

