// Fill out your copyright notice in the Description page of Project Settings.


#include "Fishing/Public/Actor/InteractableActor.h"
#include "Components/CapsuleComponent.h"
#include "Fishing/FishingCharacter.h"

// Sets default values
AInteractableActor::AInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AInteractableActor::BeginOverlap);
}

void AInteractableActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FishingCharacter = Cast<AFishingCharacter>(OtherActor);
	if (IsValid(FishingCharacter))
	{
		FishingCharacter->Interact_Implementation(StaticMesh);
		Destroy();
	}
}
