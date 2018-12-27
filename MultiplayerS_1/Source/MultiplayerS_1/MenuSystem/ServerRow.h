// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuSystem/MenuWidget.h"
#include "ServerRow.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERS_1_API UServerRow : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerName;

	UPROPERTY(meta = (BindWidget))
	class UButton* RowButton;
	
	void Setup(class UMainMenu* Parent, uint32 Index);

private:

	uint32 Index;

	UPROPERTY()
	UMainMenu* MainMenu;

	UFUNCTION()
	void OnRowButtonClicked();
};
