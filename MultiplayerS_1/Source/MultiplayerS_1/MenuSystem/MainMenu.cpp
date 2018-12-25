// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "UObject/ConstructorHelpers.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "ServerRow.h"

UMainMenu::UMainMenu(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowWBPClass(TEXT("/Game/Menu/WBP_ServerRow"));
	if (!ServerRowWBPClass.Class) { return; }

	ServerRowClass = ServerRowWBPClass.Class;
}

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) { return false; };

	if (!HostButton) { return false; }
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!JoinButton) { return false; }
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!BackButton) { return false; }
	BackButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!JoinMenuJoinButton) { return false; }
	JoinMenuJoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if (!QuitButton) { return false; }
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

	return true;
}

void UMainMenu::PopulateServerList(TArray<FString> ServerNames)
{
	UWorld* World = GetWorld();
	if (!World) { return; }

	ServerList->ClearChildren();

	for (const FString& ServerName : ServerNames)
	{
		UServerRow* ServerRow = CreateWidget<UServerRow>(World, ServerRowClass);
		ServerRow->ServerName->SetText(FText::FromString(ServerName));
		ServerList->AddChild(ServerRow);
	}
}

void UMainMenu::HostServer()
{
	if (MenuInterface) { MenuInterface->Host(); }
}

void UMainMenu::JoinServer()
{
	if (MenuInterface) { MenuInterface->Join(""); }
}

void UMainMenu::OpenJoinMenu()
{
	if (!MenuSwitcher) { return; }
	if (!JoinMenu) { return; }

	MenuSwitcher->SetActiveWidget(JoinMenu);

	if (!MenuInterface) { return; }
	MenuInterface->RefreshServerList();
}

void UMainMenu::OpenMainMenu()
{
	if (!MenuSwitcher) { return; }
	if (!MainMenu) { return; }

	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::QuitGame()
{
	APlayerController* Player = GetWorld()->GetFirstPlayerController();
	//UE_LOG(LogTemp, Warning, TEXT("Quit"))
	Player->ConsoleCommand("quit");
}
