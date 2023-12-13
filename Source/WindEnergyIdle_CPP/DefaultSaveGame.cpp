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
	return LastLevelNumber;
}

int UDefaultSaveGame::SetLastLevelNumber(int Value)
{
	LastLevelNumber = Value;
	return LastLevelNumber;
}

