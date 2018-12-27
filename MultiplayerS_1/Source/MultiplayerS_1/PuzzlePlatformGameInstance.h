// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"

#include "MenuSystem/MenuInterface.h"
#include "PuzzlePlatformGameInstance.generated.h"

const static FName SESSION_NAME = TEXT("GameSession");

UCLASS()
class MULTIPLAYERS_1_API UPuzzlePlatformGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
public:

	UPuzzlePlatformGameInstance(const FObjectInitializer & ObjectInitializer);

	virtual void Init() override;

	IOnlineSessionPtr SessionInterface;

	UFUNCTION(BlueprintCallable)
	void LoadMenuWidget();

	UFUNCTION(BlueprintCallable)
	void LoadInGameMenu();
	
	UFUNCTION(Exec)
	void Host();

	void CreateSession();

	UFUNCTION(Exec)
	void Join(uint32 Index);

	UFUNCTION(Exec)
	void ReturnToMainMenu();
	
	UFUNCTION()
	void RefreshServerList();

private:

	class UMainMenu* MainMenu;

	TSubclassOf<class UUserWidget> MenuClass;

	TSubclassOf<class UUserWidget> InGameMenuClass;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	void OnCreateSessionComplete(FName SessionName, bool bSucceded);
	void OnDestroySessionComplete(FName SessionName, bool bSucceded);
	void OnFindSessionComplete(bool bSucceded);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
};
