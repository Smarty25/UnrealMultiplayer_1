// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERS_1_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetMenuInterface(IMenuInterface* MenuInterfaceToSet);

	void Setup();
	void OnLevelRemovedFromWorld(ULevel* Inlevel, UWorld* InWorld) override;

private:

	IMenuInterface * MenuInterface;

	UPROPERTY(meta = (BindWidget))
	class UButton* Host_Button;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Join_Button;

	UFUNCTION()
	void Host_ButtonOnClick();

protected:

	virtual bool Initialize() override;

};
