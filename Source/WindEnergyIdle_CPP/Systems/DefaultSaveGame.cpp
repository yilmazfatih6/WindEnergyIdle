// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultSaveGame.h"

int UDefaultSaveGame::GetMaxLevelNumber() const
{
	return MaxLevelNumber;
}

int UDefaultSaveGame::SetMaxLevelNumber(int Value)
{
	MaxLevelNumber = Value;
	return MaxLevelNumber;
}

int UDefaultSaveGame::GetLastLevelNumber() const
{
	UE_LOG(LogTemp, Log, TEXT("[UDefaultSaveGame]GetLastLevelNumber()=%d"), LastLevelNumber);
	return LastLevelNumber;
}

int UDefaultSaveGame::SetLastLevelNumber(int Value)
{
	UE_LOG(LogTemp, Log, TEXT("[UDefaultSaveGame] SetLastLevelNumber() Value = %d"), Value);
	LastLevelNumber = Value;
	return LastLevelNumber;
}

