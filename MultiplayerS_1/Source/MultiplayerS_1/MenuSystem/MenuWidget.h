// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERS_1_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetMenuInterface(IMenuInterface* MenuInterfaceToSet);

	void Setup();

	void OnLevelRemovedFromWorld(ULevel* Inlevel, UWorld* InWorld) override;

protected:

	IMenuInterface * MenuInterface;
};
