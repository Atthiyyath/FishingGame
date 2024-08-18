// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Throwable.h"

#include "Actor/Water.h"
#include "Components/SphereComponent.h"
#include "Fishing/FishingCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "HUD/FishingHUD.h"

// Sets default values
AThrowable::AThrowable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);

	BuoyancyComponent = CreateDefaultSubobject<UBuoyancyComponent>(TEXT("BuoyancyComponent"));

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
}

void AThrowable::OnReleased(FVector ForwardVector, AFishingCharacter* Character)
{
	CharacterOwner = Cast<AFishingCharacter>(Character);
	if (!IsValid(CharacterOwner)) return;
	
	ForwardVector *= CharacterOwner->GetHoldTime();
	StaticMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
	StaticMesh->AddImpulse(ForwardVector);
}

// Called when the game starts or when spawned
void AThrowable::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AThrowable::BeginOverlap);
}

void AThrowable::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsBobberFloating)
	{		
		if (!IsValid(CharacterOwner)) return;
		if (!CharacterOwner->GetStartFishingTime()) return;
		if (!CharacterOwner->GetIsFishingAnimationActive()) return;
		
		CharacterOwner->FishingTime += DeltaSeconds;
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Emerald, FString::Printf(TEXT("FishingTime %f"), CharacterOwner->FishingTime));
		if (CharacterOwner->FishingTime >= InitTimeFishBites)
		{
			CharacterOwner->SetPlayerCaughtFish(true);
		}
		else
		{
			CharacterOwner->SetPlayerCaughtFish(false);
		}

		CharacterOwner->GetHUD()->OnTextHelper.Broadcast("Click LMB for pull the bobber!");
	}
}

void AThrowable::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Water = Cast<AWater>(OtherActor);
	if (IsValid(Water))
	{
		IsBobberFloating = true;
	}
}