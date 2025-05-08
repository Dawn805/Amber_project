// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "SaveGame/VolumeSave.h"

void UMainGameInstance::Init()
{
	Super::Init();

	Backpack = NewObject<UBackpackComponent>(this, UBackpackComponent::StaticClass());
	Backpack->RegisterComponent();
}

