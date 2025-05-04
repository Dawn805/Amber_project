// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "LevelJump.generated.h"

UCLASS()
class AMBER_PROJECT_API ALevelJump : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevelJump();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName JumpLevelName = "No";
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName OldLevelName = "No";

	UFUNCTION(BlueprintCallable)
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector StartLocation;
};
