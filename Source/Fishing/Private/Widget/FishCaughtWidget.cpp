// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/FishCaughtWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/FishDataAsset.h"

void UFishCaughtWidget::ShowCatchLayer(bool IsFishCaught)
{
	if (!FishDataAsset) return;
	const int32 RandomID = FMath::RandRange(0, 2);
	
	if (IsFishCaught)
	{
		auto Image = FishDataAsset->AssetItems[RandomID].FishImage;
		auto Name = FishDataAsset->AssetItems[RandomID].FishName;
		auto Desc = FishDataAsset->AssetItems[RandomID].FishDesc;
		auto Length = FishDataAsset->AssetItems[RandomID].FishLength;

		FishImage->SetBrushFromTexture(Image);
		FishName->SetText(FText::FromString(Name));
		FishDesc->SetText(FText::FromString(Desc));
		FishLength->SetText(FText::FromString(FString::SanitizeFloat(Length)));
	}
	else
	{
		FishImage->SetBrushFromTexture(nullptr);
		FishName->SetText(FText::FromString("Fish Escaped!"));
		FishDesc->SetText(FText::FromString(""));
		FishLength->SetText(FText::FromString(FString::SanitizeFloat(0.f)));
	}
}
