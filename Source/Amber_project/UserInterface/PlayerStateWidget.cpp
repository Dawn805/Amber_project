// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateWidget.h"

#include "Backpack.h"
#include "Amber_project/MainPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UPlayerStateWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	if (!PlayerController) return;
	
	AMainPaperZDCharacter* ZdCharacter = Cast<AMainPaperZDCharacter>(PlayerController->GetPawn());
	if (PlayerController->BackpackWidgetInstance != nullptr)
	{
		ZdCharacter = PlayerController->BackpackWidgetInstance->CurrentCharacter;
	}
	if (!ZdCharacter) return;
	
	float HPPercent = ZdCharacter->StateComponent->HP/ZdCharacter->StateComponent->HP_Max;
	HPPercent = FMath::Clamp(HPPercent, 0.0f, 1.0f);
	HPBar->SetPercent(HPPercent);

	float MPPercent = ZdCharacter->StateComponent->MP/ZdCharacter->StateComponent->MP_Max;
	MPPercent = FMath::Clamp(MPPercent, 0.0f, 1.0f);
	MPBar->SetPercent(MPPercent);
}
