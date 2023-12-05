// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelStreamer.h"

#include "WEI_GameInstance.h"

// Sets default values
ALevelStreamer::ALevelStreamer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelStreamer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelStreamer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelStreamer::LoadCurrentLevel()
{
	auto gameInstance = static_cast<UWEI_GameInstance>(GetGameInstance());
}

