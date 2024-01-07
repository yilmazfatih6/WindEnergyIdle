// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceManager.h"

#include "WindEnergyIdle_CPP/DataAssets/ResourceDataAsset.h"


// Sets default values for this component's properties
UResourceManager::UResourceManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UResourceManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UResourceManager::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UResourceManager::AddResource(EResourceType Type, int Amount)
{
	for (const auto Resource : Resources)
	{
		if(Resource->Type == Type)
		{
			Resource->Amount += Amount;
			OnResourceAdded.Broadcast(Resource);
			return;
		}
	}
}

void UResourceManager::RemoveResource(const EResourceType Type, const int Amount)
{
	for (const auto Resource : Resources)
	{
		if(Resource->Type == Type)
		{
			if(Resource->Amount < Amount)
			{
				UE_LOG(LogTemp, Log, TEXT("[UResourceManager] RemoveResource, Amount of %hhd is less than %d"), Type, Amount);
				return;
			}
			
			Resource->Amount -= Amount;
			OnResourceRemoved.Broadcast(Resource);
			return;
		}
	}
}

int UResourceManager::GetResource(EResourceType Type)
{
	for (const auto Resource : Resources)
	{
		if(Resource->Type == Type)
		{
			return Resource->Amount;
		}
	}
	return -1;
}


