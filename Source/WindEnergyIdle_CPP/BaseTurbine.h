// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTurbine.generated.h"

UCLASS()
class WINDENERGYIDLE_CPP_API ABaseTurbine : public AActor
{
	GENERATED_BODY()

public:
	bool bIsOverlapping;
	
public:	
	// Sets default values for this actor's properties
	ABaseTurbine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSelected();
	void SetUnselected();
};
