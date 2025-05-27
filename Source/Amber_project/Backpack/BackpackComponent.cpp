// Fill out your copyright notice in the Description page of Project Settings.


#include "BackpackComponent.h"


// Sets default values for this component's properties
UBackpackComponent::UBackpackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UBackpackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBackpackComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int UBackpackComponent::HasItem(FBackpackItems NewItem)
{
	for (int i = 0 ; i < Backpack_Items.Num(); i++)
	{
		if (Backpack_Items[i].ItemName == NewItem.ItemName)
		{
			return i;
		}
	}
	return -1;
}

void UBackpackComponent::AddItem(FBackpackItems NewItem)
{
	int sub = HasItem(NewItem);
	if (sub == -1)
	{
		Backpack_Items.Add(NewItem);
		return;
	}
	Backpack_Items[sub].ItemCount += 1;
}

void UBackpackComponent::UseItem(FBackpackItems NewItem)
{
	int sub = HasItem(NewItem);
	if (sub == -1) return;

	Backpack_Items[sub].ItemCount -= 1;

	if (Backpack_Items[sub].ItemCount == 0)
	{
		Backpack_Items.RemoveAt(sub);
	}
}




