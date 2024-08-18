// Copyright Epic Games, Inc. All Rights Reserved.

#include "FishingCharacter.h"

#include "FishingPlayerController.h"
#include "Actor/Throwable.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Public/HUD/FishingHUD.h"

AFishingCharacter::AFishingCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	EquipItem = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EquipItem"));
	EquipItem->SetupAttachment(GetMesh(), "hand_lSocket");
	
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AFishingCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
	
}

void AFishingCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<AFishingPlayerController>(GetController());
	if (!IsValid(PlayerController))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("Player Controller is nullptr!")));
	}
	
	FishingHUD = Cast<AFishingHUD>(PlayerController->GetHUD());
	if (!IsValid(FishingHUD))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("HUD is nullptr!")));
	}

	//EndDelegate.BindUObject(this, &AFishingCharacter::OnAnimationEnded);
}

void AFishingCharacter::Interact_Implementation(UStaticMeshComponent* StaticMesh)
{
	IInteractInterface::Interact_Implementation(StaticMesh);
	
	EquipItem->SetStaticMesh(StaticMesh->GetStaticMesh());
	IsItemEquipped = true;
}

void AFishingCharacter::ThrowBobber()
{
	if (IsInFishingArea && IsItemEquipped)
	{
		IsFishingAnimationActive = true;
	}
}

/*void AFishingCharacter::OnAnimationEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsFishingAnimationActive = true;
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}*/

void AFishingCharacter::OnThrowableItemReleased()
{
	if (!IsValid(ThrowableItemClass)) return;
	ThrowableItem = GetWorld()->SpawnActor<AThrowable>(ThrowableItemClass);
	
	if (!IsValid(ThrowableItem)) return;
	ThrowableItem->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("hand_lSocket"));
	ThrowableItem->OnReleased(GetCapsuleComponent()->GetForwardVector(), this);
}
