// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERS_1_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:

	AMovingPlatform();

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 10;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget))
	FVector TargetLocation;

	void Activate();
	void Deactivate();
	
protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	bool bIsActivated = false;

	FVector GlobalTargetLocation;
	FVector GlobalStartLocation;
	
};
