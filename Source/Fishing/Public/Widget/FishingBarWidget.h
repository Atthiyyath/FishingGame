// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FishingBarWidget.generated.h"

class UOverlay;
class UProgressBar;
/**
 * 
 */
UCLASS()
class FISHING_API UFishingBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPercentageBar(float Value);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> OverlayBar;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar;
};
