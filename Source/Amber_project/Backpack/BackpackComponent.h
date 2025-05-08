// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BackpackComponent.generated.h"


USTRUCT(BlueprintType)
struct FBackpackItems
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int ItemCount = 1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* ItemIcon;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AMBER_PROJECT_API UBackpackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBackpackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable)
	void AddItem(FBackpackItems NewItem);
	UFUNCTION(BlueprintCallable)
	void UseItem(FBackpackItems NewItem);

	UFUNCTION(BlueprintCallable)
	int HasItem(FBackpackItems NewItem);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBackpackItems> Items;
};
