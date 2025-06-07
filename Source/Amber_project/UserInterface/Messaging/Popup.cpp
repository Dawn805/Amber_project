// Fill out your copyright notice in the Description page of Project Settings.


#include "Popup.h"

void UPopup::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Yes->OnClicked.AddDynamic(this,&UPopup::On_Button_Yes_Clicked);
}

void UPopup::On_Button_Yes_Clicked()
{
	RemoveFromParent();	
}