// Copyright Epic Games, Inc. All Rights Reserved.

#include "FishingPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "FishingCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HUD/FishingHUD.h"

AFishingPlayerController::AFishingPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void AFishingPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	PlayerCharacter = Cast<AFishingCharacter>(GetCharacter());
	if (!IsValid(PlayerCharacter))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("Player Character is nullptr!")));
	}
}

void AFishingPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AFishingPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AFishingPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AFishingPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AFishingPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AFishingPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &AFishingPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &AFishingPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &AFishingPlayerController::OnTouchReleased);

		// Setup touch throw events
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Started, this, &AFishingPlayerController::OnThrowStarted);
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Ongoing, this, &AFishingPlayerController::OnThrowOngoing);
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Completed, this, &AFishingPlayerController::OnThrowReleased);
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Canceled, this, &AFishingPlayerController::OnTouchReleased);
	}
}

void AFishingPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void AFishingPlayerController::OnSetDestinationTriggered()
{	
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AFishingPlayerController::OnSetDestinationReleased()
{	
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}
	
	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void AFishingPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void AFishingPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void AFishingPlayerController::OnThrowStarted()
{
	HoldTime = 0.f;
}

void AFishingPlayerController::OnThrowOngoing()
{
	if (!IsValid(PlayerCharacter)) return;
		
	// NOTE:: Fishing finished
	if (PlayerCharacter->GetIsFishingAnimationActive())
	{
		PlayerCharacter->SetIsFishingAnimationActive(false);
		PlayerCharacter->SetStartFishingTime(false);
		PlayerCharacter->FishingTime = 0.f;
		
		return;
	}

	// NOTE:: Start increasing the bar
	if (PlayerCharacter->GetIsInFishingArea() && PlayerCharacter->GetIsEquipFishingRod())
	{
		/*PlayerCharacter->GetHUD()->OnActivatedFishingBarWidget.Broadcast();*/
		HoldTime += 1.f;

		if (HoldTime >= 5.f)
		{
			PlayerCharacter->GetHUD()->OnThrowParameterValue.Broadcast(HoldTime);
			PlayerCharacter->GetCharacterMovement()->DisableMovement();
		}
	}
}

void AFishingPlayerController::OnThrowReleased()
{
	if (!IsValid(PlayerCharacter)) return;

	PlayerCharacter->ThrowBobber();
	PlayerCharacter->SetHoldTime(HoldTime *= 100.f);
	PlayerCharacter->GetHUD()->OnDeactivatedWidget.Broadcast();
}