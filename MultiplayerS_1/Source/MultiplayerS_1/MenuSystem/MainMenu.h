// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuSystem/MenuWidget.h"
#include "MainMenu.generated.h"

USTRUCT()
struct FServerData 
{
	GENERATED_BODY()

	FString Name;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;
	FString HostUsername;
};

/**
 * 
 */
UCLASS()
class MULTIPLAYERS_1_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

public:

	UMainMenu(const FObjectInitializer & ObjectInitializer);

	void PopulateServerList(TArray<FServerData> ServerDataSet);

	void SetSelectedIndex(uint32 Index);

private:

	TSubclassOf<class UUserWidget> ServerRowClass;

	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinMenuJoinButton;

	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* ServerList;

	/*UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* IPTextBox;*/

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void QuitGame();

	TOptional<uint32> SelectedIndex;

protected:

	virtual bool Initialize() override;

};
