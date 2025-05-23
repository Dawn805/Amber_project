#include "Settings.h"
#include "EnhancedInputSubsystems.h"
#include "Components/WidgetSwitcher.h"
#include "Amber_project/MainPlayerController.h"
#include "Amber_project/Audio/MainMusicManager.h"
#include "Amber_project/SaveGame/MainGameUserSettings.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
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
	if (Button_Window)
		Button_Window->OnClicked.AddDynamic(this, &USettings::Button_Window_OnClicked);

	SelectorToKeyID.Add(InputKeySelector_MoveLeft, 0);
	SelectorToKeyID.Add(InputKeySelector_MoveRight, 1);
	SelectorToKeyID.Add(InputKeySelector_Jump, 2);
	SelectorToKeyID.Add(InputKeySelector_Attack_J, 3);
	SelectorToKeyID.Add(InputKeySelector_Attack_U, 4);
	SelectorToKeyID.Add(InputKeySelector_Attack_I, 5);

	TempKeyMap = UKeySaveLibrary::GetStatKeyMap();

	RefreshKeySelectors();

	if (Button_Save)
		Button_Save->OnClicked.AddDynamic(this, &USettings::Button_Save_OnClicked);
	if (Button_Reset)
		Button_Reset->OnClicked.AddDynamic(this,&USettings::Button_Reset_OnClicked);



	UMainGameUserSettings* WSettings = Cast<UMainGameUserSettings>(GEngine->GetGameUserSettings());

	//音频设置
	if (Slider_MasterVolume)
		Slider_MasterVolume->OnValueChanged.AddDynamic(this,&USettings::OnSlider_MasterVolume_ValueChange);
	if (Slider_BGMVolume)
		Slider_BGMVolume->OnValueChanged.AddDynamic(this,&USettings::OnSlider_BGMVolume_ValueChange);
	if (Slider_SoundVolume)
		Slider_SoundVolume->OnValueChanged.AddDynamic(this,&USettings::OnSlider_SoundVolume_ValueChange);
	
	if (WSettings)
	{
		VolumeSettings.MasterVolume = WSettings->GetVolumeSettings().MasterVolume;
		VolumeSettings.BGMVolume = WSettings->GetVolumeSettings().BGMVolume;
		VolumeSettings.SoundVolume = WSettings->GetVolumeSettings().SoundVolume;

		Slider_MasterVolume->SetValue(VolumeSettings.MasterVolume);
		Slider_BGMVolume->SetValue(VolumeSettings.BGMVolume);
		Slider_SoundVolume->SetValue(VolumeSettings.SoundVolume);
	}


	//窗口设置
	WindowMode->AddOption("Option.WindowMode.Fullscreen");
	WindowMode->AddOption("Option.WindowMode.Borderless");
	WindowMode->AddOption("Option.WindowMode.Windowed");

	WindowFPS->AddOption("Option.WindowFPS.120");
	WindowFPS->AddOption("Option.WindowFPS.60");
	WindowFPS->AddOption("Option.WindowFPS.30");

	WindowSize->AddOption("Option.WindowSize.1920x1080");
	WindowSize->AddOption("Option.WindowSize.1600x900");
	WindowSize->AddOption("Option.WindowSize.1280x720");

	WindowSync->AddOption("Option.WindowVSync.On");
	WindowSync->AddOption("Option.WindowVSync.Off");

	WindowMode->OnSelectionChanged.AddDynamic(this,&USettings::WindowMode_SelectionChanged);
	WindowFPS->OnSelectionChanged.AddDynamic(this,&USettings::WindowFPS_SelectionChanged);
	WindowSize->OnSelectionChanged.AddDynamic(this,&USettings::WindowSize_SelectionChanged);
	WindowSync->OnSelectionChanged.AddDynamic(this,&USettings::WindowSync_SelectionChanged);


	//初始化窗口设置
	//UMainGameUserSettings* WSettings = Cast<UMainGameUserSettings>(GEngine->GetGameUserSettings());
	if (WSettings)
	{
		EWindowMode::Type Mode = WSettings->GetFullscreenMode();
		if (Mode == EWindowMode::Fullscreen)
			WindowMode->SetSelectedOption("Option.WindowMode.Fullscreen");
		if (Mode == EWindowMode::WindowedFullscreen)
			WindowMode->SetSelectedOption("Option.WindowMode.Borderless");
		if (Mode == EWindowMode::Windowed)
			WindowMode->SetSelectedOption("Option.WindowMode.Windowed");

		int FPS = WSettings->GetWindowsSettings().WindowFPS;
		if (FPS == 120)
			WindowFPS->SetSelectedOption("Option.WindowFPS.120");
		if (FPS == 60)
			WindowFPS->SetSelectedOption("Option.WindowFPS.60");
		if (FPS == 30)
			WindowFPS->SetSelectedOption("Option.WindowFPS.30");

		FIntPoint Size = WSettings->GetScreenResolution();
		if (Size == FIntPoint(1920, 1080))
			WindowSize->SetSelectedOption("Option.WindowSize.1920x1080");
		if (Size == FIntPoint(1600, 900))
			WindowSize->SetSelectedOption("Option.WindowSize.1600x900");
		if (Size == FIntPoint(1280, 720))
			WindowSize->SetSelectedOption("Option.WindowSize.1280x720");

		if (WSettings->IsVSyncEnabled())
			WindowSync->SetSelectedOption("Option.WindowVSync.On");
		else
			WindowSync->SetSelectedOption("Option.WindowVSync.Off");

		OldSettings.WindowMode = Mode;
		OldSettings.WindowFPS = FPS;
		OldSettings.WindowSize = Size;
		OldSettings.WindowSync = WSettings->IsVSyncEnabled();

		NewSettings.WindowMode = Mode;
		NewSettings.WindowFPS = FPS;
		NewSettings.WindowSize = Size;
		NewSettings.WindowSync = WSettings->IsVSyncEnabled();
	}


	//弹窗设置
	if (Button_Apply)
		Button_Apply->OnClicked.AddDynamic(this,&USettings::Button_Apply_OnClicked);
}

void USettings::NativeOnInitialized()
{
	WindowMode->OnGenerateWidgetEvent.BindDynamic(this,&USettings::OnWindowModeContext);
	WindowFPS->OnGenerateWidgetEvent.BindDynamic(this,&USettings::OnWindowFPSContext);
	WindowSize->OnGenerateWidgetEvent.BindDynamic(this,&USettings::OnWindowSizeContext);
	WindowSync->OnGenerateWidgetEvent.BindDynamic(this,&USettings::OnWindowSyncContext);
}


void USettings::Button_KeysChange_OnClicked()
{
	ShowWitchPanel(Panel_KeysChange);
}

void USettings::Button_Sound_OnClicked()
{
	ShowWitchPanel(Panel_Sound);
}

void USettings::Button_Window_OnClicked()
{
	ShowWitchPanel(Panel_Window);
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


void USettings::OnKeySelected_MoveLeft(UInputKeySelector* Selector,FInputChord SelectedChord)
{
	Selector = this->InputKeySelector_MoveLeft;
	if (!Selector) return;

	int* FindID = SelectorToKeyID.Find(Selector);
	if (!FindID) return;
	TempKeyMap[*FindID] = SelectedChord.Key;
}
void USettings::OnKeySelected_MoveRight(UInputKeySelector* Selector,FInputChord SelectedChord)
{
	Selector = this->InputKeySelector_MoveRight;
	if (!Selector) return;

	int* FindID = SelectorToKeyID.Find(Selector);
	if (!FindID) return;
	TempKeyMap[*FindID] = SelectedChord.Key;
}
void USettings::OnKeySelected_Jump(UInputKeySelector* Selector,FInputChord SelectedChord)
{
	Selector = this->InputKeySelector_Jump;
	if (!Selector) return;

	int* FindID = SelectorToKeyID.Find(Selector);
	if (!FindID) return;
	TempKeyMap[*FindID] = SelectedChord.Key;
}
void USettings::OnKeySelected_Attack_J(UInputKeySelector* Selector,FInputChord SelectedChord)
{
	Selector = this->InputKeySelector_Attack_J;
	if (!Selector) return;

	int* FindID = SelectorToKeyID.Find(Selector);
	if (!FindID) return;
	TempKeyMap[*FindID] = SelectedChord.Key;
}
void USettings::OnKeySelected_Attack_I(UInputKeySelector* Selector,FInputChord SelectedChord)
{
	Selector = this->InputKeySelector_Attack_I;
	if (!Selector) return;

	int* FindID = SelectorToKeyID.Find(Selector);
	if (!FindID) return;
	TempKeyMap[*FindID] = SelectedChord.Key;
}
void USettings::OnKeySelected_Attack_U(UInputKeySelector* Selector,FInputChord SelectedChord)
{
	Selector = this->InputKeySelector_Attack_U;
	if (!Selector) return;

	int* FindID = SelectorToKeyID.Find(Selector);
	if (!FindID) return;
	TempKeyMap[*FindID] = SelectedChord.Key;
}


void USettings::Button_Save_OnClicked()
{
	UKeySaveLibrary::SetStatKeyMap(TempKeyMap);
	RefreshKeySelectors();

	UInputMappingContext* NewMappingContext = NewObject<UInputMappingContext>(this);
	for (int i = 0 ; i < InputMappingContext->GetMappings().Num(); i++)
	{
		NewMappingContext->MapKey(InputMappingContext->GetMappings()[i].Action,TempKeyMap[i]);
	}

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if(PC && PC->GetLocalPlayer())
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = PC->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

		if(Subsystem)
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputMappingContext_Controller, 0);
			Subsystem->AddMappingContext(NewMappingContext, 1);
		}
	}

	InputMappingContext = NewMappingContext;
}

void USettings::Button_Reset_OnClicked()
{
	TempKeyMap = UKeySaveLibrary::ResetStatKeyMap();
	UKeySaveLibrary::SetStatKeyMap(TempKeyMap);
	RefreshKeySelectors();

	UInputMappingContext* DefaultMappingContext = NewObject<UInputMappingContext>(this);
	for (int i = 0 ; i < InputMappingContext->GetMappings().Num(); i++)
	{
		DefaultMappingContext->MapKey(InputMappingContext->GetMappings()[i].Action,TempKeyMap[i]);
	}

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if(PC && PC->GetLocalPlayer())
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = PC->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

		if(Subsystem)
		{
			//Subsystem->RemoveMappingContext(InputMappingContext);
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputMappingContext_Controller, 0);
			Subsystem->AddMappingContext(DefaultMappingContext, 1);
		}
	}

	InputMappingContext = DefaultMappingContext;
}



//音频设置
void USettings::OnSlider_MasterVolume_ValueChange(float value)
{
	VolumeSettings.MasterVolume = value;
	UMainGameUserSettings* UserSettings = Cast<UMainGameUserSettings>(GEngine->GetGameUserSettings());
	if (UserSettings)
	{
		UserSettings->VolumeSettings.MasterVolume = value;
		UserSettings->SaveSettings();
		
		UMainMusicManager* MusicManager = GetWorld()->GetSubsystem<UMainMusicManager>();
		if (MusicManager)
		{
			MusicManager->ApplyVolume();
		}
	}
}

void USettings::OnSlider_BGMVolume_ValueChange(float value)
{
	VolumeSettings.BGMVolume = value;
	UMainGameUserSettings* UserSettings = Cast<UMainGameUserSettings>(GEngine->GetGameUserSettings());
	if (UserSettings)
	{
		UserSettings->VolumeSettings.BGMVolume = value;
		UserSettings->SaveSettings();

		UMainMusicManager* MusicManager = GetWorld()->GetSubsystem<UMainMusicManager>();
		if (MusicManager)
		{
			MusicManager->ApplyVolume();
		}
	}
}

void USettings::OnSlider_SoundVolume_ValueChange(float value)
{
	VolumeSettings.SoundVolume = value;
	UMainGameUserSettings* UserSettings = Cast<UMainGameUserSettings>(GEngine->GetGameUserSettings());
	if (UserSettings)
	{
		UserSettings->VolumeSettings.SoundVolume = value;
		UserSettings->SaveSettings();
		
		UMainMusicManager* MusicManager = GetWorld()->GetSubsystem<UMainMusicManager>();
		if (MusicManager)
		{
			MusicManager->ApplyVolume();
		}
	}
}


//窗口设置
UWidget* USettings::OnWindowModeContext(FString Item)
{
	UTextBlock* TextWidget = this->WidgetTree->ConstructWidget<UTextBlock>();
	TextWidget->SetText(FText::FromStringTable("/Game/Text/Misc", Item));
	return TextWidget;
}

UWidget* USettings::OnWindowFPSContext(FString Item)
{
	UTextBlock* TextWidget = this->WidgetTree->ConstructWidget<UTextBlock>();
	TextWidget->SetText(FText::FromStringTable("/Game/Text/Misc", Item));
	return TextWidget;
}

UWidget* USettings::OnWindowSizeContext(FString Item)
{
	UTextBlock* TextWidget = this->WidgetTree->ConstructWidget<UTextBlock>();
	TextWidget->SetText(FText::FromStringTable("/Game/Text/Misc", Item));
	return TextWidget;
}

UWidget* USettings::OnWindowSyncContext(FString Item)
{
	UTextBlock* TextWidget = this->WidgetTree->ConstructWidget<UTextBlock>();
	TextWidget->SetText(FText::FromStringTable("/Game/Text/Misc", Item));
	return TextWidget;
}




void USettings::WindowMode_SelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int Mode = 1;
	if (SelectedItem == "Option.WindowMode.Fullscreen")
		Mode = 0;
	if (SelectedItem == "Option.WindowMode.Borderless")
		Mode = 1;
	if (SelectedItem == "Option.WindowMode.Windowed") 
		Mode = 2;

	NewSettings.WindowMode = Mode;
}

void USettings::WindowFPS_SelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int FPS = 60;
	if (SelectedItem == "Option.WindowFPS.30")
		FPS = 30;
	if (SelectedItem == "Option.WindowFPS.60")
		FPS = 60;
	if (SelectedItem == "Option.WindowFPS.120")
		FPS = 120;

	NewSettings.WindowFPS = FPS;
}

void USettings::WindowSize_SelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	FIntPoint Size = FIntPoint(1600,900);
	if (SelectedItem == "Option.WindowSize.1920x1080")
		Size = FIntPoint(1920, 1080);
	if (SelectedItem == "Option.WindowSize.1600x900")
		Size = FIntPoint(1600, 900);
	if (SelectedItem == "Option.WindowSize.1280x720")
		Size = FIntPoint(1280, 720);

	NewSettings.WindowSize = Size;
}

void USettings::WindowSync_SelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	bool Sync = true;
	if (SelectedItem == "Option.WindowVSync.On")
		Sync = true;
	if (SelectedItem == "Option.WindowVSync.Off") 
		Sync = false;

	NewSettings.WindowSync = Sync;
}


//弹窗设置
void USettings::Button_Apply_OnClicked()
{
	UConfirmDialogWidget* Dialog = CreateWidget<UConfirmDialogWidget>(GetWorld(),ConfrimDialogClass);
	if (Dialog && ConfrimDialogClass)
	{
		Dialog->AddToViewport();
		Dialog->Init(
			this,
			FSimpleDelegate::CreateUObject(this, &USettings::ApplySettings),
			FSimpleDelegate::CreateUObject(this, &USettings::RollbackSettings),
			10.0f);
	}

	UMainGameUserSettings* UserSettings = Cast<UMainGameUserSettings>(GEngine->GetGameUserSettings());
	if (UserSettings)
	{
		UserSettings->UpdateWindowSettings(NewSettings);
	}
}

void USettings::ApplySettings()
{
	UMainGameUserSettings* UserSettings = Cast<UMainGameUserSettings>(GEngine->GetGameUserSettings());
	if (UserSettings)
	{
		UserSettings->UpdateWindowSettings(NewSettings);
	}
	OldSettings = NewSettings;
}

void USettings::RollbackSettings()
{
	UMainGameUserSettings* UserSettings = Cast<UMainGameUserSettings>(GEngine->GetGameUserSettings());
	if (UserSettings)
	{
		UserSettings->UpdateWindowSettings(OldSettings);
	}
	
	if (OldSettings.WindowMode == EWindowMode::Fullscreen)
		WindowMode->SetSelectedOption("Option.WindowMode.Fullscreen");
	if (OldSettings.WindowMode == EWindowMode::WindowedFullscreen)
		WindowMode->SetSelectedOption("Option.WindowMode.Borderless");
	if (OldSettings.WindowMode == EWindowMode::Windowed)
		WindowMode->SetSelectedOption("Option.WindowMode.Windowed");
	
	if (OldSettings.WindowFPS == 120)
		WindowFPS->SetSelectedOption("Option.WindowFPS.120");
	if (OldSettings.WindowFPS == 60)
		WindowFPS->SetSelectedOption("Option.WindowFPS.60");
	if (OldSettings.WindowFPS == 30)
		WindowFPS->SetSelectedOption("Option.WindowFPS.30");
	
	if (OldSettings.WindowSize == FIntPoint(1920, 1080))
		WindowSize->SetSelectedOption("Option.WindowSize.1920x1080");
	if (OldSettings.WindowSize == FIntPoint(1600, 900))
		WindowSize->SetSelectedOption("Option.WindowSize.1600x900");
	if (OldSettings.WindowSize == FIntPoint(1280, 720))
		WindowSize->SetSelectedOption("Option.WindowSize.1280x720");

	if (OldSettings.WindowSync == true)
		WindowSync->SetSelectedOption("Option.WindowVSync.On");
	else
		WindowSync->SetSelectedOption("Option.WindowVSync.Off");
}
