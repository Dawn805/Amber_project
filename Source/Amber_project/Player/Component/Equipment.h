// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Amber_project/Backpack/EquipmentComponent.h"
#include "Components/ActorComponent.h"
#include "Equipment.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AMBER_PROJECT_API UEquipment : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEquipment();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FEquipComponent Equip_Slot0;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FEquipComponent Equip_Slot1;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FEquipComponent Equip_Slot2;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FEquipComponent Equip_Slot3;

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<bool> Slots = {false,false,false,false};
};
