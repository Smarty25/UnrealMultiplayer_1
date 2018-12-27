// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerRow.h"
#include "Components/Button.h"
#include "MainMenu.h"

void UServerRow::Setup(UMainMenu* Parent, uint32 Index)
{
	if (!RowButton) { return; }
	RowButton->OnClicked.AddDynamic(this, &UServerRow::OnRowButtonClicked);

	MainMenu = Parent;
	UServerRow::Index = Index;
}

void UServerRow::OnRowButtonClicked()
{
	MainMenu->SetSelectedIndex(Index);
}

