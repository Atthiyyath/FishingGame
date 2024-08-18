// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/FishingBarWidget.h"

#include "Components/ProgressBar.h"

void UFishingBarWidget::SetPercentageBar(float Value)
{
	ProgressBar->SetPercent(Value);
}
