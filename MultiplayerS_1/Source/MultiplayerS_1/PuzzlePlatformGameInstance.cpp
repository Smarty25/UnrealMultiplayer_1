// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Engine/Engine.h"
#include "OnlineSessionSettings.h"
#include "OnlineSessionInterface.h"

#include "MenuSystem/MainMenu.h"
#include "MenuSystem/MenuWidget.h"

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWBPClass(TEXT("/Game/Menu/WBP_MainMenu"));
	if (!MainMenuWBPClass.Class) { return; }
	
	MenuClass = MainMenuWBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuWBPClass(TEXT("/Game/Menu/WBP_InGameMenu"));
	if (!InGameMenuWBPClass.Class) { return; }

	InGameMenuClass = InGameMenuWBPClass.Class;
}

void UPuzzlePlatformGameInstance::Init()
{
	Super::Init();

	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();

	if (OnlineSubsystem != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *OnlineSubsystem->GetSubsystemName().ToString());
		SessionInterface = OnlineSubsystem->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnCreateSessionComplete);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OnlineSubsystem not found."))
	}
}

void UPuzzlePlatformGameInstance::LoadMenuWidget()
{
	if (!MenuClass) { return; }

	UMainMenu* Menu = CreateWidget<UMainMenu>(this, MenuClass);

	Menu->Setup();

	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformGameInstance::LoadInGameMenu()
{
	if (!InGameMenuClass) { return; }

	UMenuWidget* InGameMenu = CreateWidget<UMenuWidget>(this, InGameMenuClass);

	InGameMenu->Setup();

	InGameMenu->SetMenuInterface(this);
}

void UPuzzlePlatformGameInstance::Host()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;
		SessionInterface->CreateSession(0, TEXT("GameSession"), SessionSettings);
	}
}

void UPuzzlePlatformGameInstance::OnCreateSessionComplete(FName SessionName, bool bSucceded)
{
	if (!bSucceded)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not able to create session."));
		return;
	}
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

void UPuzzlePlatformGameInstance::ReturnToMainMenu()
{
	UEngine* Engine = GetEngine();
	if (!Engine) { return; }

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Returning to Main Menu")));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!PlayerController) { return; }

	PlayerController->ClientTravel("/Game/Menu/L_MainMenu", ETravelType::TRAVEL_Absolute);
}
