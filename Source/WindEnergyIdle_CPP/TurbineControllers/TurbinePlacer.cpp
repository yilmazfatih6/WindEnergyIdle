// Fill out your copyright notice in the Description page of Project Settings.


#include "TurbinePlacer.h"

#include "Kismet/GameplayStatics.h"
#include "WindEnergyIdle_CPP/Ground.h"
#include "WindEnergyIdle_CPP/Turbines/BaseTurbine.h"

class ABaseTurbine;
// Sets default values for this component's properties
UTurbinePlacer::UTurbinePlacer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

// Called when the game starts
void UTurbinePlacer::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void UTurbinePlacer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
		
	HoverSelectedTurbine();
}

void UTurbinePlacer::HoverSelectedTurbine()
{
	if(!bHover) return;

	if(!TargetTurbine) return;

	PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	const FVector TraceEnd = WorldLocation + WorldDirection * TraceDistance;

	QueryParams.AddIgnoredActor(GetOwner());
	
	GetWorld()->LineTraceSingleByChannel(Hit, WorldLocation, TraceEnd, TraceChannelPropertyGround, QueryParams);

	const AGround* Ground = static_cast<AGround*>(Hit.GetActor());

	// if(Hit.GetActor()->IsA(TSubclassOf<AGround>)
	// {
	// 	UE_LOG(LogTemp, Log, TEXT("Hit actor is not type of AGround"));
	// 	return;
	// }
	
	if(Ground == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Ground is null!"));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Hit %s"), *Hit.GetActor()->GetName());
	
	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{
		// Ground->GetWindMapValue(Hit);
		TargetTurbine->SetActorLocation(Hit.ImpactPoint);
	}
}

// void UTurbinePlacer::GetWindMapValue(FHitResult Hit)
// {
	

	/*
	TextureCompressionSettings OldCompressionSettings = MyTexture2D->CompressionSettings; TextureMipGenSettings OldMipGenSettings = MyTexture2D->MipGenSettings; bool OldSRGB = MyTexture2D->SRGB;

	MyTexture2D->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
	MyTexture2D->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
	MyTexture2D->SRGB = false;
	MyTexture2D->UpdateResource();

	const FColor* FormatedImageData = static_cast<const FColor*>( MyTexture2D->PlatformData->Mips[0].BulkData.LockReadOnly());

	for(int32 X = 0; X < MyTexture2D->GetSizeX(); X++)
	{
		for (int32 Y = 0; Y < MyTexture2D->GetSizeY(); Y++)
		{
			FColor PixelColor = FormatedImageData[Y * MyTexture2D->GetSizeX() + X];
			if(PixelColor.R + PixelColor.G + PixelColor.B + PixelColor.A > 0)
			{
				UE_LOG(LogTemp, Log, TEXT("[GetWindmap] Pixel Color: %f, %f, %f, %f"), PixelColor.R, PixelColor.G, PixelColor.B, PixelColor.A);
			}
		}
	} 

	MyTexture2D->PlatformData->Mips[0].BulkData.Unlock();
	*/
	
	// UPrimitiveComponent* HitComponent = HitResult.GetComponent();
	// UMaterialInterface* Material = HitComponent->GetMaterial(HitResult.Item);
	// FName TextureParameterName = FName("Windmap"); // Replace with your parameter name
	// UTexture* TextureToWrite = nullptr;
	//
	// if (Material)
	// {
	// 	auto bIsSuccessful = Material->GetTextureParameterValue(TextureParameterName, TextureToWrite);
	// 	if (bIsSuccessful)
	// 	{
	// 		UTexture2D* TextureToWrite2D = static_cast<UTexture2D*>(TextureToWrite);
	//
	// 		FTexture2DMipMap* Mip = &TextureToWrite2D->PlatformData->Mips[0]; // Assuming you want the first mip level
	//
	// 		int32 Width = Mip->SizeX;
	// 		int32 Height = Mip->SizeY;
	//
	// 		FColor* FormatedImageData = new FColor[Width * Height];
	// 		Mip->BulkData.GetCopy(reinterpret_cast<void**>(FormatedImageData));
	//
	// 		// Calculate the UV coordinates based on the hit location
	// 		FVector2D HitUV;
	// 		Material->GetTextureParameterValueUV(TextureParameterName, HitResult.ImpactPoint, HitResult.ImpactNormal, HitUV);
	//
	// 		// Convert UV coordinates to texture coordinates
	// 		int32 TextureX = FMath::Clamp(FMath::RoundToInt(HitUV.X * Width), 0, Width - 1);
	// 		int32 TextureY = FMath::Clamp(FMath::RoundToInt(HitUV.Y * Height), 0, Height - 1);
	//
	// 		// Get the color at the calculated texture coordinates
	// 		FColor HitColor = TextureData[TextureY * Width + TextureX];
	//
	// 		// Now you have the color at the hit point.
	// 	}
	// 	}
	// }

	


	
	
	
	// // Check if the hit component has a texture (e.g., a Material with a texture parameter)
 //    FName ParameterName("YourTextureParameterName"); // Replace with the actual parameter name
	// UTexture* Texture = nullptr;
	// UMaterialInstanceDynamic* MaterialInstance = nullptr;
	// bool bWasSuccessful = false;
 //
	// if (HitResult.GetComponent())
	// {
	// 	UPrimitiveComponent* HitComponent = HitResult.GetComponent();
	// 	UMaterialInterface* Material = HitComponent->GetMaterial(HitResult.Item);
	// 	MaterialInstance = Cast<UMaterialInstanceDynamic>(Material);
 //
	// 	if (MaterialInstance)
	// 	{
	// 		bWasSuccessful = MaterialInstance->GetTextureParameterValue(ParameterName, Texture);
	// 	}
	// }
 //
 //
	// if (bWasSuccessful)
	// {
	// 	UTexture2D* Texture2D = static_cast<UTexture2D>(Texture);
 //
	// 	// Now, you can access the pixel values from the texture
	// 	FTexture2DMipMap* Mip = &Texture->PlatformData->Mips[0];
	// 	FColor* FormattedImageData = static_cast<FColor*>(Mip->BulkData.GetData());
 //
	// 	// Access the pixel value at a specific UV coordinate within the texture
	// 	FVector2D UVCoordinate = HitResult.uv;
	// 	FColor PixelColor = FormattedImageData[FMath::Clamp(static_cast<int32>(UVCoordinate.X * Mip->SizeX), 0, Mip->SizeX - 1)];
 //
	// 	// Use PixelColor for further processing
	// }
// }

void UTurbinePlacer::SetTargetTurbine(ABaseTurbine* Turbine)
{
	TargetTurbine = Turbine;
}

void UTurbinePlacer::SetHover(bool value)
{
	bHover = value && TargetTurbine != nullptr;
}

void UTurbinePlacer::Place()
{
	if(!TargetTurbine) return;

	if(TargetTurbine->IsOverlapping())
	{
		TargetTurbine->StartMovement(TargetTurbine->GetPlacementLocation());
		OnPlacementFail.Broadcast(TargetTurbine);
		UE_LOG(LogTemp, Log, TEXT("[UTurbinePlacer] Place, Placement failed due to overlap! Turbine: %s"), *TargetTurbine->GetName());
	}
	else
	{
		TargetTurbine->Place();
		OnPlace.Broadcast(TargetTurbine);
		UE_LOG(LogTemp, Log, TEXT("[UTurbinePlacer] Place, Turbine: %s"), *TargetTurbine->GetName());
	}

	if(!TargetTurbine->IsInitialPlacement())
		TargetTurbine = nullptr;
	// UE_LOG(LogTemp, Log, TEXT("[WEI_Pawn] PlaceSelectedTurbine, Turbine: %s"), *PreviouslySelectedTurbine->GetName());
}
