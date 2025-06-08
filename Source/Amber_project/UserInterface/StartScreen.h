// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SelectCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "StartScreen.generated.h"

/**
 * 
 */
UCLASS()
class AMBER_PROJECT_API UStartScreen : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	//开始游戏按钮
	UPROPERTY(meta = (BindWidget))
	UButton* Button_StartGame;
	//继续游戏按钮
	UPROPERTY(meta = (BindWidget))
	UButton* Button_ContinueGame;
	//退出游戏按钮
	UPROPERTY(meta = (BindWidget))
	UButton* Button_ExitGame;
	//设置按钮
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Settings;

	//绑定对应的函数
	UFUNCTION(BlueprintCallable)
	void On_StartGame_Clicked();
	UFUNCTION(BlueprintCallable)
	void On_ContinueGame_Clicked();
	UFUNCTION(BlueprintCallable)
	void On_ExitGame_Clicked();
	UFUNCTION(BlueprintCallable)
	void On_Settings_Clicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USelectCharacter> SelectCharacterClass;
	UPROPERTY()
	USelectCharacter* SelectCharacterInstance = nullptr;
};
