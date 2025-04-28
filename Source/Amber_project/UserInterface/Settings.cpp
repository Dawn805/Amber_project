#include "Settings.h"
#include "EnhancedInputSubsystems.h"
#include "Components/WidgetSwitcher.h"
#include "Amber_project/MainPlayerController.h"

void USettings::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_KeysChange)
		Button_KeysChange->OnClicked.AddDynamic(this, &USettings::Button_KeysChange_OnClicked);
	if (Button_Sound)
		Button_Sound->OnClicked.AddDynamic(this, &USettings::Button_Sound_OnClicked);
	if (Button_ComeBack)
		Button_ComeBack->OnClicked.AddDynamic(this, &USettings::Button_Come_Back_OnClicked);

	if (Button_Reset)
		Button_Reset->OnClicked.AddDynamic(this, &USettings::Button_Reset_OnClicked);


	KeysChangeManager = NewObject<UKeysChangeManager>(this);
	if (APlayerController* PC = GetOwningPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			KeysChangeManager->Initialize(Subsystem);
		}
	}

	SelectorToKeyID.Add(InputKeySelector_MoveLeft, 0);
	SelectorToKeyID.Add(InputKeySelector_MoveRight, 1);
	SelectorToKeyID.Add(InputKeySelector_Jump, 2);
	SelectorToKeyID.Add(InputKeySelector_Attack_J, 3);
	SelectorToKeyID.Add(InputKeySelector_Attack_U, 4);
	SelectorToKeyID.Add(InputKeySelector_Attack_I, 5);

	for (auto& Elem : SelectorToKeyID)
	{
		UInputKeySelector* Selector = Elem.Key;
		int32 KeyID = Elem.Value;
		if (Selector && KeysChangeManager && KeysChangeManager->KeySaveObject)
		{
			TMap<int32, FKey> CurrentMap = KeysChangeManager->GetKeyMap();
			if (CurrentMap.Contains(KeyID))
			{
				Selector->SetSelectedKey(CurrentMap[KeyID]);
			}
		}
	}

}

void USettings::Button_KeysChange_OnClicked()
{
	ShowWitchPanel(Panel_KeysChange);
}

void USettings::Button_Sound_OnClicked()
{
	ShowWitchPanel(Panel_Sound);
}

void USettings::Button_Come_Back_OnClicked()
{
	if (AMainPlayerController* MainPlayerController = Cast<AMainPlayerController>(GetOwningPlayer()))
	{
		MainPlayerController->CloseSettings();
	}
}

void USettings::ShowWitchPanel(UCanvasPanel* Panel)
{
	if (SettingsSwitcher && Panel)
	{
		SettingsSwitcher->SetActiveWidget(Panel);
	}
}


void USettings::Button_Reset_OnClicked()
{
	if (KeysChangeManager)
	{
		KeysChangeManager->ResetKeyMap();
	}

	for (auto& Elem : SelectorToKeyID)
	{
		UInputKeySelector* Selector = Elem.Key;
		int32 KeyID = Elem.Value;
		if (Selector && KeysChangeManager && KeysChangeManager->KeySaveObject)
		{
			TMap<int32, FKey> CurrentMap = KeysChangeManager->GetKeyMap();
			if (CurrentMap.Contains(KeyID))
			{
				Selector->SetSelectedKey(CurrentMap[KeyID]);
			}
		}
	}
}