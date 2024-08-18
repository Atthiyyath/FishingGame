// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/FishingHUD.h"

#include "FCTween.h"
#include "Widget/GameplayCoreWidget.h"

void AFishingHUD::BeginPlay()
{
	Super::BeginPlay();

	GameplayWidget = CreateWidget<UGameplayCoreWidget>(GetOwningPlayerController(), GameplayWidgetRef);
	if (IsValid(GameplayWidget))
	{
		GameplayWidget->AddToViewport();
	}

	OnThrowParameterValue.AddUObject(this, &AFishingHUD::SetThrowParameterValue);
	OnPullingBobber.AddUObject(this, &AFishingHUD::ActivateFishingWidget);
	OnTextHelper.AddUObject(this, &AFishingHUD::SetTextHelper);
	//OnActivatedFishingBarWidget.AddUObject(this, &AFishingHUD::ActivatedFishingBarWidget);
	OnDeactivatedWidget.AddUObject(this, &AFishingHUD::DeactivatedWidget);
}

void AFishingHUD::SetThrowParameterValue(float value)
{
	value /= 100.f;
	if (!IsValid(GameplayWidget)) return;
	GameplayWidget->SetPercentageBar(value);
}

void AFishingHUD::ActivateFishingWidget(bool IsFishCaught)
{
	if (!IsValid(GameplayWidget)) return;
	GameplayWidget->ShowCatchLayer(IsFishCaught);
}

void AFishingHUD::SetTextHelper(FString String)
{
	if (!IsValid(GameplayWidget)) return;
	GameplayWidget->SetTextHelper(String);
}

void AFishingHUD::ActivatedFishingBarWidget()
{
	if (!IsValid(GameplayWidget)) return;
	GameplayWidget->ActivatedWidget();
}

void AFishingHUD::DeactivatedWidget()
{
	if (!IsValid(GameplayWidget)) return;
	GameplayWidget->DeactivatedWidget();
}
