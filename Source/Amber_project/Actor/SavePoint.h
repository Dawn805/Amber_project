// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "SavePoint.generated.h"

UCLASS()
class AMBER_PROJECT_API ASavePoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASavePoint();
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult);
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UPaperSpriteComponent* SpriteComp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBoxComponent* BoxComp;
};
