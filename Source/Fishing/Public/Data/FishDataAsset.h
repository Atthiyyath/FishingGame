// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FishDataAsset.generated.h"

USTRUCT()
struct FFishAssetInfo {
	GENERATED_BODY()
			 
	UPROPERTY(EditAnywhere)
	FString FishName;

	UPROPERTY(EditAnywhere)
	FString FishDesc;

	UPROPERTY(EditAnywhere)
	float FishLength;
			 
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> FishImage;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMesh> SKM_Fish;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimationAsset> AnimFish;
};

/**
 * 
 */
UCLASS()
class FISHING_API UFishDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FFishAssetInfo> AssetItems;
};
