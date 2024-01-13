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

	for (const auto Resource : Resources)
	{
		Resource->Amount = Resource->DefaultAmount;
	}
}


// Called every frame
void UResourceManager::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UResourceManager::AddResource(EGameResourceType Type, float Amount)
{
	Amount = FMath::Clamp(Amount, 0, Amount);

	if(&Resources == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[UResourceManager] AddResource, Resources is null!"));
		return;
	}
	
	for (const auto Resource : Resources)
	{
		if(Resource == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("[UResourceManager] AddResource, Resource is null!"));
			break;
		}
		
		if(Resource->Type == Type)
		{
			UE_LOG(LogTemp, Log, TEXT("[UResourceManager] AddResource, Type %d, Amount %d"), Resource->Type, Amount);
			Resource->Amount += Amount;
			OnResourceAdded.Broadcast(Resource);
			return;
		}
	}
}

void UResourceManager::RemoveResource(const EGameResourceType Type, float Amount)
{
	Amount = FMath::Clamp(Amount, 0, Amount);

	if(&Resources == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[UResourceManager] RemoveResource, Resources is null!"));
		return;
	}
	
	for (const auto Resource : Resources)
	{
		if(Resource->Type == Type)
		{
			if(Resource->Amount < Amount)
			{
				UE_LOG(LogTemp, Log, TEXT("[UResourceManager] RemoveResource, Amount of %hhd is less than %f"), Type, Amount);
				return;
			}

			UE_LOG(LogTemp, Log, TEXT("[UResourceManager] RemoveResource, Type %hhd, Amount %f"), Resource->Type, Amount);
			Resource->Amount -= Amount;
			OnResourceRemoved.Broadcast(Resource);
			return;
		}
	}
}

 UResourceDataAsset* UResourceManager::GetResource(EGameResourceType Type)
{
	if(&Resources == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[UResourceManager] AddResource, Resources is null!"));
		return nullptr;
	}
	
	for (const auto Resource : Resources)
	{
		if(Resource->Type == Type)
		{
			return Resource;
		}
	}
	return nullptr;
}


