// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"

void UMenuWidget::SetMenuInterface(IMenuInterface* MenuInterfaceToSet)
{
	MenuInterface = MenuInterfaceToSet;
}

void UMenuWidget::Setup()
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

void UMenuWidget::OnLevelRemovedFromWorld(ULevel* Inlevel, UWorld* InWorld)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) { return; }

	PlayerController->bShowMouseCursor = false;

	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);

	this->RemoveFromViewport();
}
