// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) { return false; }

	if (!HostButton) { return false; }
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!JoinButton) { return false; }
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!BackButton) { return false; }
	BackButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!JoinMenuJoinButton) { return false; }
	JoinMenuJoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	return true;
}



void UMainMenu::HostServer()
{
	if (MenuInterface) { MenuInterface->Host(); }
}

void UMainMenu::JoinServer()
{
	FString Address = IPTextBox->GetText().ToString();
	if (MenuInterface) { MenuInterface->Join(Address); }
}

void UMainMenu::OpenJoinMenu()
{
	if (!MenuSwitcher) { return; }
	if (!JoinMenu) { return; }

	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenMainMenu()
{
	if (!MenuSwitcher) { return; }
	if (!MainMenu) { return; }

	MenuSwitcher->SetActiveWidget(MainMenu);
}
