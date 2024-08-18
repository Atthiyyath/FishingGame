// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/FishingArea.h"

#include "Components/BoxComponent.h"
#include "Fishing/FishingCharacter.h"
#include "HUD/FishingHUD.h"

// Sets default values
AFishingArea::AFishingArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
}

// Called when the game starts or when spawned
void AFishingArea::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AFishingArea::BeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AFishingArea::EndOverlap);
}

void AFishingArea::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FishingCharacter = Cast<AFishingCharacter>(OtherActor);
	if (!IsValid(FishingCharacter)) return;
	if (!FishingCharacter->GetIsEquipFishingRod()) return;
	
	// NOTE:: Create timer .2f before fishing to give the player prepare time before fishing
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([this]
	{
		FishingCharacter->SetIsInFishingArea(true);
		FishingCharacter->GetHUD()->OnTextHelper.Broadcast("You can fishing here. Hold LMB for throw the bobber!");
	}), .2f, false);
}

void AFishingArea::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	FishingCharacter = Cast<AFishingCharacter>(OtherActor);
	if (!IsValid(FishingCharacter)) return;

	FishingCharacter->SetIsInFishingArea(false);
	FishingCharacter->GetHUD()->OnDeactivatedWidget.Broadcast();
}

