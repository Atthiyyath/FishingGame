// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotifyStartFishingTime.generated.h"

class AFishingCharacter;
/**
 * 
 */
UCLASS()
class FISHING_API UAnimNotifyStartFishingTime : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	TObjectPtr<AFishingCharacter> PlayerCharacter;
};
