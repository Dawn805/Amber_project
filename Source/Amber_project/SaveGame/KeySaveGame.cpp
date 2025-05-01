// Fill out your copyright notice in the Description page of Project Settings.


#include "KeySaveGame.h"

UKeySaveGame::UKeySaveGame()
{
	DefaultKeyMap = {
		{0, EKeys::A},
		{1, EKeys::D},
		{2, EKeys::K},
		{3, EKeys::J},
		{4, EKeys::U},
		{5, EKeys::I}
	};
	CurrentKeyMap = DefaultKeyMap;
}

TMap<int,FKey> UKeySaveGame::GetKeyMap()
{
	return CurrentKeyMap;
}

void UKeySaveGame::SetKeyMap(const TMap<int,FKey>& NewKeyMap)
{
	CurrentKeyMap = NewKeyMap;
}

TMap<int,FKey> UKeySaveGame::ResetKeyMap()
{
	return DefaultKeyMap;
}



