// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/AnimNotifyStartFishingTime.h"

#include "Fishing/FishingCharacter.h"

void UAnimNotifyStartFishingTime::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                         const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		PlayerCharacter = Cast<AFishingCharacter>(MeshComp->GetOwner());
		if (!IsValid(PlayerCharacter)) return;
		PlayerCharacter->SetStartFishingTime(true);
	}
}
