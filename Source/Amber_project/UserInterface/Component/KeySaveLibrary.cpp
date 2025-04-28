// Fill out your copyright notice in the Description page of Project Settings.


#include "KeySaveLibrary.h"

#include "Kismet/GameplayStatics.h"

void UKeySaveLibrary::CreateSave()
{
	if (!UGameplayStatics::DoesSaveGameExist("KeySave",0))
	{
		UKeySaveGame* NewSave = Cast<UKeySaveGame>(UGameplayStatics::CreateSaveGameObject(UKeySaveGame::StaticClass()));
		if (NewSave)
		{
			UGameplayStatics::SaveGameToSlot(NewSave,"KeySave",0);
		}
	}
}

UKeySaveGame* UKeySaveLibrary::GetSave()
{
	if (!UGameplayStatics::DoesSaveGameExist("KeySave",0))
	{
		CreateSave();
	}

	return Cast<UKeySaveGame>(UGameplayStatics::LoadGameFromSlot("KeySave",0));
}

TMap<int, FKey> UKeySaveLibrary::GetStatKeyMap()
{
	UKeySaveGame* SaveGame = GetSave();
	if (SaveGame)
	{
		return SaveGame->GetKeyMap();
	}
	return TMap<int,FKey>();
}

void UKeySaveLibrary::SetStatKeyMap(TMap<int,FKey>& InKeyMap)
{
	UKeySaveGame* SaveGame = GetSave();
	if (SaveGame)
	{
		SaveGame->SetKeyMap(InKeyMap);
		UGameplayStatics::SaveGameToSlot(SaveGame,"KeySave",0);
	}
}

void UKeySaveLibrary::ResetStatKeyMap()
{
	UKeySaveGame* SaveGame = GetSave();
	if (SaveGame)
	{
		SaveGame->ResetKeyMap();
		UGameplayStatics::SaveGameToSlot(SaveGame,"KeySave",0);
	}
}

