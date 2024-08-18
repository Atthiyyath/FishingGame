// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FishingHUD.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnThrowParameterValue, float)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPullingBobber, bool)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTextHelper, FString)
DECLARE_MULTICAST_DELEGATE(FOnActivatedFishingBarWidget)
DECLARE_MULTICAST_DELEGATE(FOnDeactivatedWidget)

class UGameplayCoreWidget;
/**
 * 
 */
UCLASS()
class FISHING_API AFishingHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	void SetThrowParameterValue(float value);
	void ActivateFishingWidget(bool IsFishCaught);
	void SetTextHelper(FString String);
	void ActivatedFishingBarWidget();
	void DeactivatedWidget();

public:
	FOnThrowParameterValue OnThrowParameterValue;
	FOnPullingBobber OnPullingBobber;
	FOnTextHelper OnTextHelper;
	FOnDeactivatedWidget OnDeactivatedWidget;
	FOnActivatedFishingBarWidget OnActivatedFishingBarWidget;
	
	UPROPERTY(EditDefaultsOnly, Category = "Reference")
	TSubclassOf<UGameplayCoreWidget> GameplayWidgetRef;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UGameplayCoreWidget> GameplayWidget;
};
