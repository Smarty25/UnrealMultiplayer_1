// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMenu.h"
#include "Components/Button.h"

bool UInGameMenu::Initialize()
{
	bool bSuccess = Super::Initialize();
	if (!bSuccess) { return false; }

	if (!MainMenuButton) { return false; }
	MainMenuButton->OnClicked.AddDynamic(this, &UInGameMenu::ReturnToMainMenu);

	if (!CancelButton) { return false; }
	CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CloseInGameMenu);

	return true;
}

void UInGameMenu::ReturnToMainMenu()
{
	if (MenuInterface) { MenuInterface->ReturnToMainMenu(); }
}

void UInGameMenu::CloseInGameMenu()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) { return; }

	PlayerController->bShowMouseCursor = false;

	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);

	this->RemoveFromViewport();
}

