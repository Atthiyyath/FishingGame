// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextHelperWidget.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class FISHING_API UTextHelperWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetTextHelper(FString String);
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextHelper;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image;
};
