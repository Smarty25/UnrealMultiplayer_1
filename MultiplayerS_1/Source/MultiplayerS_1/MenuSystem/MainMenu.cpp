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

void UMainMenu::Setup()
{
	this->AddToViewport();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) { return; }

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
}

void UMainMenu::OnLevelRemovedFromWorld(ULevel* Inlevel, UWorld* InWorld)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) { return; }

	PlayerController->bShowMouseCursor = false;

	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);

	this->RemoveFromViewport();
}

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterfaceToSet)
{
	MenuInterface = MenuInterfaceToSet;
}

void UMainMenu::Host_ButtonOnClick()
{
	if (MenuInterface) { MenuInterface->Host(); UE_LOG(LogTemp, Warning, TEXT("Host Button Clicked")) }
}
