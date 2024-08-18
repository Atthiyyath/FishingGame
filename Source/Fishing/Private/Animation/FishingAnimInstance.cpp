// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/FishingAnimInstance.h"

#include "Fishing/FishingCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void UFishingAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PlayerCharacter = Cast<AFishingCharacter>(TryGetPawnOwner());
	if (!IsValid(PlayerCharacter)) return;
	
	MovementComp = PlayerCharacter->GetCharacterMovement();
}

void UFishingAnimInstance::UpdateProperties()
{
	Velocity = MovementComp->Velocity;
	GroundSpeed = Velocity.Size2D();
	ShouldMove = GroundSpeed > 3.f;
	IsFalling = MovementComp->IsFalling();
	IsFishing = PlayerCharacter->GetIsFishingAnimationActive();
}

void UFishingAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(PlayerCharacter))
	{
		UpdateProperties();
	}
	else
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFishingCharacter::StaticClass(), OutActors);
		for (auto Actor : OutActors)
		{
			PlayerCharacter = Cast<AFishingCharacter>(Actor);
			if (IsValid(PlayerCharacter))
			{
				UpdateProperties();
				break;
			}
		}
	}
}
