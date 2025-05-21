// Fill out your copyright notice in the Description page of Project Settings.


#include "ConfirmDialogWidget.h"

void UConfirmDialogWidget::Init(UObject* WorldContext, FSimpleDelegate Yes, FSimpleDelegate No, float whentime)
{
	OnYes = Yes;
	OnNo = No;
	RemainingTime = whentime;
}

void UConfirmDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Yes->OnClicked.AddDynamic(this,&UConfirmDialogWidget::OnYesClicked);
	Button_No->OnClicked.AddDynamic(this,&UConfirmDialogWidget::OnNoClicked);
}

void UConfirmDialogWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	OneTime = OneTime + InDeltaTime;
	if (OneTime >= 1.0f)
	{
		OneTime = 0.0f;
		UpdateCountdown();
	}
}


void UConfirmDialogWidget::OnYesClicked()
{
	if (OnYes.IsBound())
	{
		OnYes.Execute();
	}
	RemoveFromParent();
}

void UConfirmDialogWidget::OnNoClicked()
{
	if (OnNo.IsBound())
	{
		OnNo.Execute();
	}
	RemoveFromParent();
}

void UConfirmDialogWidget::UpdateCountdown()
{
	if (RemainingTime <= 0.0f)
	{
		RemainingTime = 0.0f;

		if (Text_Time)
		{
			Text_Time->SetText(FText::FromString("0"));
		}
		
		OnNoClicked(); 
		return;
	}

	RemainingTime -= 1.0f;

	if (Text_Time)
	{
		FString CountdownStr = FString::Printf(TEXT("%.0f"), RemainingTime);
		Text_Time->SetText(FText::FromString(CountdownStr));
	}
}
