// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TextHelperWidget.h"

#include "Components/TextBlock.h"

void UTextHelperWidget::SetTextHelper(FString String)
{
	TextHelper->SetText(FText::FromString(String));
}
