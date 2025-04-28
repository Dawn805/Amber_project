#include "Settings.h"
#include "EnhancedInputSubsystems.h"
#include "Components/WidgetSwitcher.h"
#include "Amber_project/MainPlayerController.h"
#include "Kismet/GameplayStatics.h"

void USettings::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_KeysChange)
		Button_KeysChange->OnClicked.AddDynamic(this, &USettings::Button_KeysChange_OnClicked);
	if (Button_Sound)
		Button_Sound->OnClicked.AddDynamic(this, &USettings::Button_Sound_OnClicked);
	if (Button_ComeBack)
		Button_ComeBack->OnClicked.AddDynamic(this, &USettings::Button_Come_Back_OnClicked);

	SelectorToKeyID.Add(InputKeySelector_MoveLeft, 0);
	SelectorToKeyID.Add(InputKeySelector_MoveRight, 1);
	SelectorToKeyID.Add(InputKeySelector_Jump, 2);
	SelectorToKeyID.Add(InputKeySelector_Attack_J, 3);
	SelectorToKeyID.Add(InputKeySelector_Attack_U, 4);
	SelectorToKeyID.Add(InputKeySelector_Attack_I, 5);

	RefreshKeySelectors();
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

void USettings::RefreshKeySelectors()
{
	TMap<int,FKey> SavedKeyMap = UKeySaveLibrary::GetStatKeyMap();
	for (const TPair<UInputKeySelector*,int>& Pair : SelectorToKeyID)
	{
		UInputKeySelector* Selector = Pair.Key;
		int KeyID = Pair.Value;

		if (Selector && SavedKeyMap.Contains(KeyID))
		{
			FInputChord NewChord;
			NewChord.Key = SavedKeyMap[KeyID];

			Selector->SetSelectedKey(NewChord);
		}
	}
}
