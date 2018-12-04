// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERS_1_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

private:
		UPROPERTY(meta = (BindWidget))
		class UButton* Host_Button;
	
		UPROPERTY(meta = (BindWidget))
		class UButton* Join_Button;
protected:
	virtual bool Initialize() override;

	UFUNCTION()
	void Host_ButtonOnClick();
};
