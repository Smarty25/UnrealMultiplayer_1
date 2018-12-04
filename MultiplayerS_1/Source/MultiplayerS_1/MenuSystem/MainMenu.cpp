// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) { return false; }

	if (!Host_Button) { return false; }
	Host_Button->OnClicked.AddDynamic(this, &UMainMenu::Host_ButtonOnClick);

	return true;
}

void UMainMenu::Host_ButtonOnClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Host Button Clicked"))
}
