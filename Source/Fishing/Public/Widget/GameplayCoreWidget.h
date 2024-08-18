// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayCoreWidget.generated.h"

class UTextHelperWidget;
class UFishingBarWidget;
class UFishCaughtWidget;
class UTextBlock;
class UProgressBar;
class UOverlay;
/**
 * 
 */
UCLASS()
class FISHING_API UGameplayCoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPercentageBar(float value);
	void ShowCatchLayer(bool IsFishCaught);
	void SetTextHelper(FString String);
	void ActivatedWidget();
	void DeactivatedWidget();

private:	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UFishCaughtWidget> WBP_FishCaughtWidget;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UFishingBarWidget> WBP_FishingBarWidget;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextHelperWidget> WBP_TextHelperWidget;
};
