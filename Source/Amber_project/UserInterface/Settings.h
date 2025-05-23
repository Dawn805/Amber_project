#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"
#include "InputCoreTypes.h"
#include "Components/InputKeySelector.h"
#include "InputMappingContext.h"
#include "Amber_project/SaveGame/MainGameUserSettings.h"
#include "Components/ComboBox.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "Messaging/ConfirmDialogWidget.h"

#include "Settings.generated.h"

UCLASS()
class AMBER_PROJECT_API USettings : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

public:
	UPROPERTY(meta = (BindWidget))
	UButton* Button_KeysChange;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Sound;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_ComeBack;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Window;

public:
	UFUNCTION(BlueprintCallable)
	void Button_KeysChange_OnClicked();
	UFUNCTION(BlueprintCallable)
	void Button_Sound_OnClicked();
	UFUNCTION(BlueprintCallable)
	void Button_Come_Back_OnClicked();
	UFUNCTION(BlueprintCallable)
	void Button_Window_OnClicked();

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> SettingsSwitcher;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> Panel_KeysChange;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> Panel_Sound;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> Panel_Window;

public:
	UFUNCTION(BlueprintCallable)
	void ShowWitchPanel(UCanvasPanel* Panel);

public:
	UPROPERTY(meta = (BindWidget))
	UInputKeySelector* InputKeySelector_MoveLeft;
	UPROPERTY(meta = (BindWidget))
	UInputKeySelector* InputKeySelector_MoveRight;
	UPROPERTY(meta = (BindWidget))
	UInputKeySelector* InputKeySelector_Jump;
	UPROPERTY(meta = (BindWidget))
	UInputKeySelector* InputKeySelector_Attack_J;
	UPROPERTY(meta = (BindWidget))
	UInputKeySelector* InputKeySelector_Attack_U;
	UPROPERTY(meta = (BindWidget))
	UInputKeySelector* InputKeySelector_Attack_I;

	UPROPERTY()
	TMap<UInputKeySelector*, int32> SelectorToKeyID;

public:
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Reset;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Save;

public:
	UFUNCTION(BlueprintCallable)
	void RefreshKeySelectors();

	TMap<int,FKey> TempKeyMap;
	
	UFUNCTION(BlueprintCallable)
	void OnKeySelected_MoveLeft(UInputKeySelector* Selector,FInputChord SelectedChord);
	UFUNCTION(BlueprintCallable)
	void OnKeySelected_MoveRight(UInputKeySelector* Selector,FInputChord SelectedChord);
	UFUNCTION(BlueprintCallable)
	void OnKeySelected_Jump(UInputKeySelector* Selector,FInputChord SelectedChord);
	UFUNCTION(BlueprintCallable)
	void OnKeySelected_Attack_J(UInputKeySelector* Selector,FInputChord SelectedChord);
	UFUNCTION(BlueprintCallable)
	void OnKeySelected_Attack_U(UInputKeySelector* Selector,FInputChord SelectedChord);
	UFUNCTION(BlueprintCallable)
	void OnKeySelected_Attack_I(UInputKeySelector* Selector,FInputChord SelectedChord);

	UFUNCTION(BlueprintCallable)
	void Button_Save_OnClicked();

	UFUNCTION(BlueprintCallable)
	void Button_Reset_OnClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputMappingContext* InputMappingContext_Controller;

public:
	//音频
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Volume")
	USoundMix* SoundMix;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Volume")
	USoundClass* SoundClass_Master;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Volume")
	USoundClass* SoundClass_BGM;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Volume")
	USoundClass* SoundClass_Sound;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FVolumeSettings VolumeSettings;
	
	UPROPERTY(meta=(BindWidget))
	USlider* Slider_MasterVolume;
	UPROPERTY(meta=(BindWidget))
	USlider* Slider_BGMVolume;
	UPROPERTY(meta=(BindWidget))
	USlider* Slider_SoundVolume;

	UFUNCTION(BlueprintCallable)
	void OnSlider_MasterVolume_ValueChange(float value);
	UFUNCTION(BlueprintCallable)
	void OnSlider_BGMVolume_ValueChange(float value);
	UFUNCTION(BlueprintCallable)
	void OnSlider_SoundVolume_ValueChange(float value);



//窗口设置
public:
	UPROPERTY(meta=(BindWidget))
	UComboBoxString* WindowMode;
	UPROPERTY(meta=(BindWidget))
	UComboBoxString* WindowFPS;
	UPROPERTY(meta=(BindWidget))
	UComboBoxString* WindowSize;
	UPROPERTY(meta=(BindWidget))
	UComboBoxString* WindowSync;

	UFUNCTION(BlueprintCallable)
	void WindowMode_SelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION(BlueprintCallable)
	void WindowFPS_SelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION(BlueprintCallable)
	void WindowSize_SelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION(BlueprintCallable)
	void WindowSync_SelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	UWidget* OnWindowModeContext(FString Item);
	UFUNCTION()
	UWidget* OnWindowFPSContext(FString Item);
	UFUNCTION()
	UWidget* OnWindowSizeContext(FString Item);
	UFUNCTION()
	UWidget* OnWindowSyncContext(FString Item);

	UPROPERTY(meta=(BindWidget))
	UButton* Button_Apply;
	UFUNCTION(BlueprintCallable)
	void Button_Apply_OnClicked();
	UFUNCTION(BlueprintCallable)
	void ApplySettings();
	UFUNCTION(BlueprintCallable)
	void RollbackSettings();
	

	//弹窗设置
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UConfirmDialogWidget> ConfrimDialogClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWindowsSettings OldSettings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWindowsSettings NewSettings;
};
