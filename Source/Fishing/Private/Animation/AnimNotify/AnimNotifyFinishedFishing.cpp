// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/AnimNotifyFinishedFishing.h"

#include "Fishing/FishingCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HUD/FishingHUD.h"

void UAnimNotifyFinishedFishing::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                        const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		PlayerCharacter = Cast<AFishingCharacter>(MeshComp->GetOwner());
		if (!IsValid(PlayerCharacter)) return;
		PlayerCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		PlayerCharacter->SetIsInFishingArea(false);
		PlayerCharacter->GetHUD()->OnPullingBobber.Broadcast(PlayerCharacter->GetPlayerCaughtFish());
	}
}
