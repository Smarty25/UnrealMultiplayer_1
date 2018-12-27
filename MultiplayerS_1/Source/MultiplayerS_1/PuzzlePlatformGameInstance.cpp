// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Engine/Engine.h"
#include "OnlineSessionSettings.h"
#include "OnlineSessionSettings.h"

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
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnFindSessionComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnJoinSessionComplete);
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

	MainMenu = CreateWidget<UMainMenu>(this, MenuClass);

	MainMenu->Setup();

	MainMenu->SetMenuInterface(this);
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
		FNamedOnlineSession* PreviousSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (PreviousSession)
		{
			SessionInterface->DestroySession(SESSION_NAME);
			UE_LOG(LogTemp, Warning, TEXT("Session destroyed."));
		}
		else
		{
			CreateSession();
		}
	}
}

void UPuzzlePlatformGameInstance::CreateSession()
{
	FOnlineSessionSettings SessionSettings;
	SessionSettings.bIsLANMatch = true;
	SessionSettings.NumPublicConnections = 2;
	SessionSettings.bShouldAdvertise = true;

	SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
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

void UPuzzlePlatformGameInstance::OnDestroySessionComplete(FName SessionName, bool bSucceded)
{
	if (bSucceded)
	{
		CreateSession();
	}
}

void UPuzzlePlatformGameInstance::OnFindSessionComplete(bool bSucceded)
{
	UE_LOG(LogTemp, Warning, TEXT("Find session complete."))
	if (bSucceded && SessionSearch.IsValid() && MainMenu)
	{
		TArray<FString> ServerNames;

		for (const FOnlineSessionSearchResult& Result : SessionSearch->SearchResults)
		{
			ServerNames.Add(Result.GetSessionIdStr());
		}

		MainMenu->PopulateServerList(ServerNames);
	}
}

void UPuzzlePlatformGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	FString ConnectInfo;
	if (!SessionInterface->GetResolvedConnectString(SessionName, ConnectInfo)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not get Connect info."))
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("ConnectInfo = %s"), *ConnectInfo)

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!PlayerController) { return; }

	PlayerController->ClientTravel(ConnectInfo, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformGameInstance::Join(uint32 Index)
{
	if (!SessionInterface.IsValid()) { return; }
	if (!SessionSearch.IsValid()) { return; }

	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);
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

void UPuzzlePlatformGameInstance::RefreshServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		SessionSearch->bIsLanQuery = true;

		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
		UE_LOG(LogTemp, Warning, TEXT("Started finding a session."))
	}
}
