// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResourceManager.generated.h"

enum class EResourceType : uint8;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FResourceDataDelegate, UResourceDataAsset*, ResourceData);

class UResourceDataAsset;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WINDENERGYIDLE_CPP_API UResourceManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable);
	FResourceDataDelegate OnResourceAdded;

	UPROPERTY(BlueprintAssignable);
	FResourceDataDelegate OnResourceRemoved;

	UPROPERTY(EditDefaultsOnly)
	TArray<UResourceDataAsset*> Resources;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UResourceManager();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void AddResource(EResourceType Type, int Amount);

	UFUNCTION(BlueprintCallable)
	void RemoveResource(EResourceType Type, int Amount);

	UFUNCTION(BlueprintCallable)
	int GetResource(EResourceType Type);
	
};
