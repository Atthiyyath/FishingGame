// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/GameplayCoreWidget.h"

#include "FCTween.h"
#include "Widget/FishCaughtWidget.h"
#include "Widget/FishingBarWidget.h"
#include "Widget/TextHelperWidget.h"

void UGameplayCoreWidget::ActivatedWidget()
{
	FCTween::Play(0.f, 1.f, [&](float x)
	{
		WBP_FishingBarWidget->SetRenderOpacity(x);
	}, .5f, EFCEase::OutCubic);

	DeactivatedWidget();
}

void UGameplayCoreWidget::SetPercentageBar(float value)
{
	WBP_FishingBarWidget->SetPercentageBar(value);
	WBP_FishingBarWidget->SetRenderOpacity(1.f);
}

void UGameplayCoreWidget::ShowCatchLayer(bool IsFishCaught)
{
	WBP_FishCaughtWidget->ShowCatchLayer(IsFishCaught);

	FCTween::Play(0.f, 1.f, [&](float x)
	{
		WBP_FishCaughtWidget->SetRenderOpacity(x);
	}, .5f, EFCEase::OutCubic);

	// NOTE:: Create timer 5.f before deactive the WBP_FishCaughtWidget
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([this]
	{
		FCTween::Play(1.f, 0.f, [&](float x)
		{
			WBP_FishCaughtWidget->SetRenderOpacity(x);
		}, .5f, EFCEase::OutCubic);
	}), 5.f, false);
}

void UGameplayCoreWidget::SetTextHelper(FString String)
{
	WBP_TextHelperWidget->SetTextHelper(String);
	WBP_TextHelperWidget->SetRenderOpacity(1.f);
}

void UGameplayCoreWidget::DeactivatedWidget()
{
	if (WBP_FishingBarWidget->GetRenderOpacity() == 1.f)
	{
		FCTween::Play(1.f, 0.f, [&](float x)
		{
			WBP_FishingBarWidget->SetRenderOpacity(x);
		}, .5f, EFCEase::OutCubic);
	}
	else if (WBP_TextHelperWidget->GetRenderOpacity() == 1.f)
	{
		FCTween::Play(1.f, 0.f, [&](float x)
		{
			WBP_TextHelperWidget->SetRenderOpacity(x);
		}, .5f, EFCEase::OutCubic);
	}
}
