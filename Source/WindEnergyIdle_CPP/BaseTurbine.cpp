// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTurbine.h"

// Sets default values
ABaseTurbine::ABaseTurbine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseTurbine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseTurbine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseTurbine::SetSelected()
{
	
}

void ABaseTurbine::SetUnselected()
{
}

