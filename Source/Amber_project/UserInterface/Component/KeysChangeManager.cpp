// Fill out your copyright notice in the Description page of Project Settings.


#include "KeysChangeManager.h"

#include "Amber_project/SaveGame/KeySaveGame.h"
#include "Kismet/GameplayStatics.h"

void UKeysChangeManager::Initialize(class UEnhancedInputLocalPlayerSubsystem* Subsystem)
{
	InputSubsystem = Subsystem;
	CreateOrLoadSave();
}

void UKeysChangeManager::SaveKeyMapping()
{
	if (KeySaveObject)
	{
		UGameplayStatics::SaveGameToSlot(KeySaveObject, SaveSlotName, 0);
	}
}

TMap<int, FKey> UKeysChangeManager::GetKeyMap()
{
	if (KeySaveObject)
	{
		return KeySaveObject->CurrentKeyMap;
	}
	return {};
}

void UKeysChangeManager::SetKeyMap(int KeyID, FKey NewKey)
{
	if (KeySaveObject)
	{
		KeySaveObject->CurrentKeyMap.Add(KeyID, NewKey);
		
		SaveKeyMapping();
	}
}

void UKeysChangeManager::ResetKeyMap()
{
	if (KeySaveObject)
	{
		KeySaveObject->CurrentKeyMap = KeySaveObject->DefaultKeyMap;

		SaveKeyMapping();
	}
}

void UKeysChangeManager::CreateOrLoadSave()
{
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName,0))
	{
		KeySaveObject = Cast<UKeySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName,0));
	}
	else
	{
		KeySaveObject = Cast<UKeySaveGame>(UGameplayStatics::CreateSaveGameObject(UKeySaveGame::StaticClass()));
		KeySaveObject->DefaultKeyMap.Add(0,EKeys::A);
		KeySaveObject->DefaultKeyMap.Add(1,EKeys::D);
		KeySaveObject->DefaultKeyMap.Add(2,EKeys::K);
		KeySaveObject->DefaultKeyMap.Add(3,EKeys::J);
		KeySaveObject->DefaultKeyMap.Add(4,EKeys::U);
		KeySaveObject->DefaultKeyMap.Add(5,EKeys::I);

		KeySaveObject->CurrentKeyMap = KeySaveObject->DefaultKeyMap;

		UGameplayStatics::SaveGameToSlot(KeySaveObject, SaveSlotName, 0);
	}
}





