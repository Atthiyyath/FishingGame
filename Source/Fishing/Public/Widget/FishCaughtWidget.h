// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FishCaughtWidget.generated.h"

class UFishDataAsset;
class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class FISHING_API UFishCaughtWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void ShowCatchLayer(bool IsFishCaught);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	TObjectPtr<UFishDataAsset> FishDataAsset;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> FishImage;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> FishName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> FishDesc;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> FishLength;
};
