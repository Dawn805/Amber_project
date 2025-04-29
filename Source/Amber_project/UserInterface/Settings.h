#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"
#include "InputCoreTypes.h"
#include "Components/InputKeySelector.h"
#include "InputMappingContext.h"

#include "Settings.generated.h"

UCLASS()
class AMBER_PROJECT_API USettings : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	UButton* Button_KeysChange;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Sound;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_ComeBack;

public:
	UFUNCTION(BlueprintCallable)
	void Button_KeysChange_OnClicked();
	UFUNCTION(BlueprintCallable)
	void Button_Sound_OnClicked();
	UFUNCTION(BlueprintCallable)
	void Button_Come_Back_OnClicked();

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> SettingsSwitcher;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> Panel_KeysChange;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> Panel_Sound;

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
};
