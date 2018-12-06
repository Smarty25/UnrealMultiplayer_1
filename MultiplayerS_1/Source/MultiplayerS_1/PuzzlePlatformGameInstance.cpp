// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Engine/Engine.h"

#include "MenuSystem/MainMenu.h"

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWBPClass(TEXT("/Game/Menu/WBP_MainMenu"));
	if (!MainMenuWBPClass.Class) { return; }
	
	MenuClass = MainMenuWBPClass.Class;
}

void UPuzzlePlatformGameInstance::Init()
{
	Super::Init();
}

void UPuzzlePlatformGameInstance::LoadMenu()
{
	if (!MenuClass) { return; }

	UMainMenu* Menu = CreateWidget<UMainMenu>(this, MenuClass);

	Menu->Setup();

	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (!Engine) { return; }

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!World) { return; }
	
	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformGameInstance::Join(const FString& IPAddress)
{
	UEngine* Engine = GetEngine();
	if (!Engine) { return; }

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Joining %s"), *IPAddress));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!PlayerController) { return; }

	PlayerController->ClientTravel(IPAddress, ETravelType::TRAVEL_Absolute);
}
